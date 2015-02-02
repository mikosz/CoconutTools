#include "NodeSelectorHas.hpp"

#include "coconut-tools/configuration/HierarchicalConfiguration.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;

bool NodeSelectorHas::matches(const HierarchicalConfiguration& node) const {
	return node.text() == nodeText_;
}

std::string NodeSelectorHas::string() const {
	return "HAS: " + nodeText_;
}
