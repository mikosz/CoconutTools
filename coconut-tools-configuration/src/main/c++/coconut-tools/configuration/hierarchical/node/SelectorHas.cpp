#include "SelectorHas.hpp"

#include "coconut-tools/configuration/hierarchical/HierarchicalConfiguration.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;
using namespace coconut_tools::configuration::hierarchical::node;

bool SelectorHas::matches(const HierarchicalConfiguration& node) const {
	return node.count(nodeSpecifier_) != 0;
}

std::string SelectorHas::string() const {
	return "HAS: " + nodeSpecifier_.string();
}
