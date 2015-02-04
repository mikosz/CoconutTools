#ifndef _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORHAS_HPP_
#define _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORHAS_HPP_

#include <string>

#include "NodeSelector.hpp"
#include "NodeSpecifier.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class NodeSelectorHas : public NodeSelector {
public:

	NodeSelectorHas(const NodeSpecifier& nodeSpecifier) :
		nodeSpecifier_(nodeSpecifier)
	{
	}

	bool matches(const HierarchicalConfiguration& node) const override;

	std::string string() const override;

protected:

	Type selectorType() const override {
		return HAS;
	}

	bool equals(const NodeSelector& other) const override {
		return nodeSpecifier_ == dynamic_cast<const NodeSelectorHas&>(other).nodeSpecifier_;
	}

private:

	NodeSpecifier nodeSpecifier_;

};

} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORHAS_HPP_ */
