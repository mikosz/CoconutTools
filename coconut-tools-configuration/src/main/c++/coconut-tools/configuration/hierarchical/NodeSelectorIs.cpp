#include "NodeSelectorIs.hpp"

#include "coconut-tools/configuration/HierarchicalConfiguration.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;

bool NodeSelectorIs::matches(const HierarchicalConfiguration& node) const {
	return node.text() == nodeText_;
}
