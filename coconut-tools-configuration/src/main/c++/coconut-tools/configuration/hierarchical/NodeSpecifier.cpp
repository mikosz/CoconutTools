#include "NodeSpecifier.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <functional>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "coconut-tools/utils/pointee.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;

namespace {

void parse(const std::string& string, std::deque<std::string>* pathParam) {
    std::deque<std::string>& path = utils::pointee(pathParam);
    boost::split(path, string, boost::is_any_of(std::string() + NodeSpecifier::SEPARATOR));
    path.erase(std::remove_if(path.begin(), path.end(), std::bind(&std::string::empty, std::placeholders::_1)), path.end());
}

} // anonymous namespace

NonEmptyNodeSpecifierExpected::NonEmptyNodeSpecifierExpected(const std::string& operation) :
    ConfigurationException(constructMessage(operation)),
    operation_(operation)
    {
}

std::string NonEmptyNodeSpecifierExpected::constructMessage(const std::string& operation) {
    std::ostringstream oss;
    oss << "Empty node specifier provided where a non-empty specifier expected while calling \""
            << operation << "\"";
    return oss.str();
}

NodeSpecifier::NodeSpecifier() {
}

NodeSpecifier::NodeSpecifier(const std::string& path) {
    parse(path, &path_);
}

NodeSpecifier::NodeSpecifier(const char* path) {
    parse(path, &path_);
}

bool NodeSpecifier::operator==(const NodeSpecifier& other) const {
    return path_ == other.path_;
}

NodeSpecifier& NodeSpecifier::operator/=(const NodeSpecifier& other) {
    std::copy(other.path_.begin(), other.path_.end(), std::back_inserter(path_));
    return *this;
}

const std::string& NodeSpecifier::root() const {
    if (path_.empty()) {
        throw NonEmptyNodeSpecifierExpected("root");
    }
    return path_.front();
}

NodeSpecifier NodeSpecifier::parentPath() const {
    if (path_.empty()) {
        throw NonEmptyNodeSpecifierExpected("parentPath");
    }
    NodeSpecifier p(*this);
    p.path_.pop_back();
    return p;
}

NodeSpecifier NodeSpecifier::childPath() const {
    if (path_.empty()) {
        throw NonEmptyNodeSpecifierExpected("childPath");
    }
    NodeSpecifier c(*this);
    c.path_.pop_front();
    return c;
}

const std::string& NodeSpecifier::child() const {
    if (path_.empty()) {
        throw NonEmptyNodeSpecifierExpected("child");
    }
    return path_.back();
}

bool NodeSpecifier::empty() const {
    return path_.empty();
}

std::string NodeSpecifier::string() const {
    return boost::join(path_, std::string() + NodeSpecifier::SEPARATOR);
}

size_t coconut_tools::configuration::hierarchical::hash_value(const NodeSpecifier& nodeSpecifier) {
    return boost::hash_value(nodeSpecifier.string());
}
