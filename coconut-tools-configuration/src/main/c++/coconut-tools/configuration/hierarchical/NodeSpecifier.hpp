#ifndef COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESPECIFIER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESPECIFIER_HPP_

#include <string>
#include <deque>

#include <boost/operators.hpp>

#include "coconut-tools/configuration/configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class NonEmptyNodeSpecifierExpected : public ConfigurationException {
public:

    NonEmptyNodeSpecifierExpected(const std::string& operation);

    ~NonEmptyNodeSpecifierExpected() throw () {
    }

    const std::string& operation() const {
        return operation_;
    }

private:

    static std::string constructMessage(const std::string& operation);

    std::string operation_;

};

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

    const std::string& root() const;

    NodeSpecifier parentPath() const;

    NodeSpecifier childPath() const;

    const std::string& child() const;

    bool empty() const;

    std::string string() const;

private:

    std::deque<std::string> path_;

};

} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

namespace std {

template <>
struct hash<coconut_tools::configuration::hierarchical::NodeSpecifier> {

	size_t operator()(const coconut_tools::configuration::hierarchical::NodeSpecifier& nodeSpecifier) const {
		return std::hash<std::string>()(nodeSpecifier.string());
	}

};

} // namespace std

#endif /* COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESPECIFIER_HPP_ */