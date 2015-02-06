#include "SelectorIs.hpp"

#include "coconut-tools/configuration/hierarchical/HierarchicalConfiguration.hpp"

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;
using namespace coconut_tools::configuration::hierarchical::node;

bool SelectorIs::matches(const HierarchicalConfiguration& node) const {
	return node.text() == nodeText_;
}

std::string SelectorIs::string() const {
	return "IS: " + nodeText_;
}
