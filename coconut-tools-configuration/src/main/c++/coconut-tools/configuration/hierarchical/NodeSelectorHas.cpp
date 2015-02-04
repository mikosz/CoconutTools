#include "NodeSelectorHas.hpp"

#include "coconut-tools/configuration/HierarchicalConfiguration.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;

bool NodeSelectorHas::matches(const HierarchicalConfiguration& node) const {
	return node.count(nodeSpecifier_) != 0;
}

std::string NodeSelectorHas::string() const {
	return "HAS: " + nodeSpecifier_.string();
}
