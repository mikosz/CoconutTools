#ifndef COCONUT_TOOLS_CONFIGURATION_HIERARCHICALCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_HIERARCHICALCONFIGURATION_HPP_

#include <iosfwd>
#include <memory>

#include <boost/operators.hpp>

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

#include "hierarchical/NodeSpecifier.hpp"
#include "Configuration.hpp"
#include "configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {

class HierarchicalConfiguration :
    public Configuration<hierarchical::NodeSpecifier, std::shared_ptr<HierarchicalConfiguration> >,
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

    size_t count(const hierarchical::NodeSpecifier& key) const;

    Value get(const hierarchical::NodeSpecifier& key) const;

    void getAll(const hierarchical::NodeSpecifier& key, Nodes* values) const;

    void set(const hierarchical::NodeSpecifier& key, ValueParam value);

    void add(const hierarchical::NodeSpecifier& key, ValueParam value);

    void erase(const hierarchical::NodeSpecifier& key);

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

    void find_(const hierarchical::NodeSpecifier& key, Nodes* nodes) const;

    Node findSingle_(
            const hierarchical::NodeSpecifier& key,
            const hierarchical::NodeSpecifier& originalKey
            ) const;

    void add_(Node parent, const std::string& childName, ValueParam value);

    void erase_(Node parent, const std::string& childName);

    void keys_(const hierarchical::NodeSpecifier& parent, Keys* k) const;

    std::ostream& print_(std::ostream& os, size_t indentation) const;

    friend std::ostream& operator<<(std::ostream& os, const HierarchicalConfiguration& configuration) {
        return configuration.print(os);
    }

};

CT_SMART_POINTER_DEFINITONS(HierarchicalConfiguration);

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_HIERARCHICALCONFIGURATION_HPP_ */
