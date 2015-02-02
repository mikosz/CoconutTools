#ifndef _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORHAS_HPP_
#define _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORHAS_HPP_

#include <string>

#include "NodeSelector.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class NodeSelectorHas : public NodeSelector {
public:

	NodeSelectorHas(const std::string& nodeText) :
		nodeText_(nodeText)
	{
	}

	bool matches(const HierarchicalConfiguration& node) const override;

	std::string string() const override;

protected:

	Type selectorType() const override {
		return HAS;
	}

	bool equals(const NodeSelector& other) const override {
		return nodeText_ == dynamic_cast<const NodeSelectorHas&>(other).nodeText_;
	}

private:

	std::string nodeText_;

};

} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTORHAS_HPP_ */
