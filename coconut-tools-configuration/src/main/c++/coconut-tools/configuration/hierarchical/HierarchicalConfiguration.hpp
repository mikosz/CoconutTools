#ifndef COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_HIERARCHICALCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_HIERARCHICALCONFIGURATION_HPP_

#include <iosfwd>
#include <memory>
#include <string>

#include <boost/operators.hpp>

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

#include "node/Path.hpp"
#include "../Configuration.hpp"
#include "../configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class AddOrSetNodePathChildHasSelector : public ConfigurationException {
public:

	AddOrSetNodePathChildHasSelector(const std::string& key) :
		key_(key)
	{
	}

	const std::string& key() const {
		return key_;
	}

private:

	std::string key_;

};

class HierarchicalConfiguration :
    public Configuration<node::Path, std::shared_ptr<HierarchicalConfiguration> >,
    public std::enable_shared_from_this<HierarchicalConfiguration>,
    public boost::equality_comparable<HierarchicalConfiguration>
{
public:

    typedef std::shared_ptr<HierarchicalConfiguration> Node;

    typedef std::vector<Node> Nodes;

    static std::shared_ptr<HierarchicalConfiguration> create(const std::string& text = std::string());

    HierarchicalConfiguration(const HierarchicalConfiguration& other);

    HierarchicalConfiguration& operator=(const HierarchicalConfiguration& other);

    bool operator==(const HierarchicalConfiguration& other) const;

    std::ostream& print(std::ostream& os) const;

    void clear();

    bool empty() const;

    size_t count(const node::Path& key) const;

    Value get(const node::Path& key) const;

    void getAll(const node::Path& key, Nodes* values) const;

    void set(const node::Path& key, ValueParam value);

    void add(const node::Path& key, ValueParam value);

    void erase(const node::Path& key);

    void keys(Keys* k) const;

    bool is(const std::string& name) const;

    const std::string& text() const {
        return text_;
    }

private:

    std::string name_;

    std::string text_;

    Nodes children_;

    HierarchicalConfiguration(
            const std::string& text,
            const std::string& name = std::string(),
            const Nodes& children = Nodes()
            );

    Node copy_() const;

    void find_(const node::Path& key, Nodes* nodes) const;

    Node findSingle_(const node::Path& key) const;

    void add_(Node parent, const node::Path::Element& child, ValueParam value);

    void erase_(Node parent, const node::Path::Element& child);

    void keys_(const node::Path& parent, Keys* k) const;

    std::ostream& print_(std::ostream& os, size_t indentation) const;

    friend std::ostream& operator<<(std::ostream& os, const HierarchicalConfiguration& configuration) {
        return configuration.print(os);
    }

};

CT_SMART_POINTER_DEFINITONS(HierarchicalConfiguration);

} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_HIERARCHICALCONFIGURATION_HPP_ */
