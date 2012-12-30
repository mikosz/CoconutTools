#ifndef COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESPECIFIER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESPECIFIER_HPP_

#include <string>
#include <deque>

#include <boost/functional/hash.hpp>
#include <boost/operators.hpp>

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class NodeSpecifier :
    public boost::dividable<NodeSpecifier>,
    public boost::equality_comparable<NodeSpecifier>
    {
public:

    static const char SEPARATOR = '/';

    NodeSpecifier();

    NodeSpecifier(const std::string& path);

    NodeSpecifier(const char* path);

    bool operator==(const NodeSpecifier& other) const;

    NodeSpecifier& operator/=(const NodeSpecifier& other);

    const std::string& front() const;

    void popFront();

    const std::string& back() const;

    void popBack();

    void pushBack(const std::string& name);

    NodeSpecifier parent() const;

    NodeSpecifier child(const std::string& name) const;

    bool empty() const;

    std::string string() const;

private:

    std::deque<std::string> path_;

};

size_t hash_value(const NodeSpecifier& nodeSpecifier);

} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESPECIFIER_HPP_ */
