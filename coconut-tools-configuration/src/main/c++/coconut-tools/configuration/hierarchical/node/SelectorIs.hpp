#ifndef _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_SELECTORIS_HPP_
#define _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_SELECTORIS_HPP_

#include <string>

#include "Selector.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {
namespace node {

class SelectorIs : public Selector {
public:

	SelectorIs(const std::string& nodeText) :
		nodeText_(nodeText)
	{
	}

	bool matches(const HierarchicalConfiguration& node) const override;

	std::string string() const override;

protected:

	Type selectorType() const override {
		return IS;
	}

	bool equals(const Selector& other) const override {
		return nodeText_ == dynamic_cast<const SelectorIs&>(other).nodeText_;
	}

private:

	std::string nodeText_;

};

} // namespace node
} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_SELECTORIS_HPP_ */
