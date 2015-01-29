#ifndef _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORIS_HPP_
#define _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORIS_HPP_

#include <string>

#include "NodeSelector.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class NodeSelectorIs : public NodeSelector {
public:

	NodeSelectorIs(const std::string& nodeText) :
		nodeText_(nodeText)
	{
	}

	bool matches(const HierarchicalConfiguration& node) const override;

protected:

	Type selectorType() const override {
		return IS;
	}

	bool equals(const NodeSelector& other) const override {
		return nodeText_ == dynamic_cast<const NodeSelectorIs&>(other).nodeText_;
	}

private:

	std::string nodeText_;

};

} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORIS_HPP_ */
