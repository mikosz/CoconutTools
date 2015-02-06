#include "Path.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <functional>
#include <iostream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
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
    oss << "Empty node specifier provided where a non-empty specifier expected while calling \""
            << operation << "\"";
    return oss.str();
}

Path::Path(ConstSelectorSharedPtr selector) :
	path_{ Element("", selector) }
{
}

Path::Path(const std::string& path, ConstSelectorSharedPtr selector) {
    parse_(path, &path_);
	if (path_.empty()) {
		path_.push_back("");
	}
	path_.back().selector = selector;
}

Path::Path(const char* path, ConstSelectorSharedPtr selector) {
	parse_(path, &path_);
	if (path_.empty()) {
		path_.push_back("");
	}
	path_.back().selector = selector;
}

bool Path::operator==(const Path& other) const {
	return path_ == other.path_;
}

Path& Path::operator/=(const Path& other) {
    std::copy(other.path_.begin(), other.path_.end(), std::back_inserter(path_));
    return *this;
}

Path Path::operator[](const Path& subSpecifier) const {
	Path result(*this);
	result.selector_ = std::make_shared<SelectorHas>(subSpecifier);
	return result;
}

Path Path::is(const std::string& text) const {
	return std::make_shared<SelectorIs>(text);
}

const std::string& Path::root() const {
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

const std::string& Path::child() const {
    if (path_.empty()) {
        throw NonEmptyPathExpected("child");
    }
    return path_.back();
}

bool Path::hasChildren() const {
    return !path_.empty();
}

std::string Path::string() const {
	std::ostringstream oss;
	oss << boost::join(path_, std::string() + Path::SEPARATOR);
	if (selector_) {
		oss << '['
			<< *selector_
			<< ']';
	}
    return  oss.str();
}

bool Path::selectorMatches(const HierarchicalConfiguration& configurationNode) const {
	if (selector_) {
		return selector_->matches(configurationNode);
	}
	return true;
}

bool Path::Element::operator==(const Element& other) const {
	if (name != other.name) {
		return false;
	} else if (static_cast<bool>(selector) != static_cast<bool>(other.selector)) {
		return false;
	} else if (selector) {
		return *selector == *other.selector;
	}
}

void Path::parse_(const std::string& pathString, Elements* pathParam) {
	Elements& path = utils::pointee(pathParam);
	boost::split(path, pathString, boost::is_any_of(std::string() + Path::SEPARATOR));
	path.erase(
		std::remove_if(
			path.begin(),
			path.end(), 
			[](const Element& e) { return e.name.empty(); }
			),
		path.end()
		);
}

std::ostream& coconut_tools::configuration::hierarchical::node::operator<<(
	std::ostream& os, const Path& specifier) {
	return os << specifier.string();
}
