#ifndef COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_PATH_HPP_
#define COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_PATH_HPP_

#include <string>
#include <deque>
#include <iosfwd>

#include <boost/operators.hpp>

#include "coconut-tools/configuration/configuration-exceptions.hpp"

#include "Selector.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class HierarchicalConfiguration;

namespace node {

class NonEmptyPathExpected : public ConfigurationException {
public:

    NonEmptyPathExpected(const std::string& operation);

    ~NonEmptyPathExpected() throw () {
    }

    const std::string& operation() const {
        return operation_;
    }

private:

    static std::string constructMessage(const std::string& operation);

    std::string operation_;

};

class Path :
    public boost::dividable<Path>,
    public boost::equality_comparable<Path>
{
public:

    static const char SEPARATOR = '/';

    Path(ConstSelectorSharedPtr selector = ConstSelectorSharedPtr());

    Path(const std::string& path, ConstSelectorSharedPtr selector = ConstSelectorSharedPtr());

    Path(const char* path, ConstSelectorSharedPtr selector = ConstSelectorSharedPtr());

    bool operator==(const Path& other) const;

    Path& operator/=(const Path& other);

	Path operator[](const Path& subSpecifier) const;

	Path is(const std::string& text) const;

    const std::string& root() const;

    Path parentPath() const;

    Path childPath() const;

    const std::string& child() const;

    bool hasChildren() const;

    std::string string() const;

	bool selectorMatches(const HierarchicalConfiguration& configurationNode) const;

private:

	struct Element {

		typedef std::string Name;

		Name name;

		ConstSelectorSharedPtr selector;

		Element(const std::string& name, ConstSelectorSharedPtr selector = ConstSelectorSharedPtr()) :
			name(name)
		{
		}

		bool operator==(const Element& other) const;

	};

	typedef std::deque<Element> Elements;

    Elements path_;

	void parse_(const std::string& string, Elements* pathParam);

};

std::ostream& operator<<(std::ostream& os, const Path& specifiers);

} // namespace node
} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

namespace std {

template <>
struct hash<coconut_tools::configuration::hierarchical::node::Path> {

	size_t operator()(const coconut_tools::configuration::hierarchical::node::Path& nodeSpecifier) const {
		return std::hash<std::string>()(nodeSpecifier.string());
	}

};

} // namespace std

#endif /* COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_PATH_HPP_ */
