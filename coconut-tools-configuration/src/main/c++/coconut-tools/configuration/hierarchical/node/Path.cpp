#include "Path.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <functional>
#include <iostream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "coconut-tools/utils/pointee.hpp"

#include "SelectorIs.hpp"
#include "SelectorHas.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;
using namespace coconut_tools::configuration::hierarchical::node;

NonEmptyPathExpected::NonEmptyPathExpected(const std::string& operation) :
    ConfigurationException(constructMessage(operation)),
    operation_(operation)
{
}

std::string NonEmptyPathExpected::constructMessage(const std::string& operation) {
    std::ostringstream oss;
    oss << "Empty node path provided where a non-empty path expected while calling \""
            << operation << "\"";
    return oss.str();
}

bool Path::Element::selectorsMatch(const HierarchicalConfiguration& configurationNode) const {
	return std::find_if_not(
		selectors.begin(),
		selectors.end(),
		[&](ConstSelectorSharedPtr selector) { return selector->matches(configurationNode); }
		) == selectors.end();
}

bool Path::Element::operator==(const Element& other) const {
	if (name != other.name) {
		return false;
	}

	return selectors == other.selectors;
}

std::string Path::Element::string() const {
	std::ostringstream oss;
	oss << name;
	for (auto selector : selectors) {
		oss << '[' << *selector << ']';
	}
	return oss.str();
}

Path::Path(const Element& element) {
	path_.push_back(element);
}

Path::Path(ConstSelectorSharedPtr selector) { // can't use initializer list here?
	Element element("", selector);
	path_.push_back(element);
}

Path::Path(const std::string& path, ConstSelectorSharedPtr selector) {
    parse_(path, &path_);
	if (path_.empty()) {
		path_.push_back(Element(""));
	}

	path_.back().selectors.push_back(selector);
}

Path::Path(const char* path, ConstSelectorSharedPtr selector) {
	parse_(path, &path_);
	if (path_.empty()) {
		path_.push_back(Element(""));
	}

	path_.back().selectors.push_back(selector);
}

bool Path::operator==(const Path& other) const {
	return path_ == other.path_;
}

Path& Path::operator/=(const Path& other) {
    std::copy(other.path_.begin(), other.path_.end(), std::back_inserter(path_));
    return *this;
}

Path Path::operator[](const Path& subPath) const {
	Path result(*this);
	if (result.path_.empty()) {
		result.path_.push_back(Element(""));
	}

	result.path_.back().selectors.push_back(std::make_shared<SelectorHas>(subPath));
	return result;
}

Path Path::is(const std::string& text) const {
	return std::make_shared<SelectorIs>(text);
}

Path Path::root() const {
    if (path_.empty()) {
        throw NonEmptyPathExpected("root");
    }

    return path_.front();
}

Path Path::parentPath() const {
    if (path_.empty()) {
        throw NonEmptyPathExpected("parentPath");
    }
    Path p(*this);
    p.path_.pop_back();
    return p;
}

Path Path::childPath() const {
    if (path_.empty()) {
        throw NonEmptyPathExpected("childPath");
    }
    Path c(*this);
    c.path_.pop_front();
    return c;
}

const Path::Element& Path::child() const {
    if (path_.empty()) {
        throw NonEmptyPathExpected("child");
    }
    return path_.back();
}

bool Path::empty() const {
    return path_.empty();
}

std::string Path::string() const {
	std::ostringstream oss;
	for (auto element : path_) {
		oss << element;
	}
    return oss.str();
}

void Path::parse_(const std::string& pathString, Elements* pathParam) {
	Elements& path = utils::pointee(pathParam);

	std::vector<std::string> pathNames;
	boost::split(pathNames, pathString, boost::is_any_of(std::string() + Path::SEPARATOR));
	pathNames.erase(
		std::remove_if(
			pathNames.begin(),
			pathNames.end(), 
			[](const Element& e) { return e.name.empty(); }
			),
		pathNames.end()
		);

	std::copy(pathNames.begin(), pathNames.end(), std::back_inserter(path));
}

std::ostream& coconut_tools::configuration::hierarchical::node::operator<<(
	std::ostream& os, const Path::Element& pathElement) {
	return os << pathElement.string();
}

std::ostream& coconut_tools::configuration::hierarchical::node::operator<<(
	std::ostream& os, const Path& path) {
	return os << path.string();
}
