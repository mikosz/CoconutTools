#include "NodeSpecifier.hpp"

#include <algorithm>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "utils/pointee.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;

namespace {

void parse(const std::string& string, std::deque<std::string>* pathParam) {
    std::deque<std::string>& path = utils::pointee(pathParam);
    boost::split(path, string, boost::is_any_of(std::string() + NodeSpecifier::SEPARATOR));
}

} // anonymous namespace

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

const std::string& NodeSpecifier::front() const {
    return path_.front();
}

void NodeSpecifier::popFront() {
    path_.pop_front();
}

const std::string& NodeSpecifier::back() const {
    return path_.back();
}

void NodeSpecifier::popBack() {
    path_.pop_back();
}

void NodeSpecifier::pushBack(const std::string& name) {
    path_.push_back(name);
}

NodeSpecifier NodeSpecifier::parent() const {
    NodeSpecifier p(*this);
    p.popBack();
    return p;
}

NodeSpecifier NodeSpecifier::child(const std::string& name) const {
    NodeSpecifier c(*this);
    c.pushBack(name);
    return c;
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
