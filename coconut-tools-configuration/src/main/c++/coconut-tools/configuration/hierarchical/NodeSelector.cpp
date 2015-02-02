#include "NodeSelector.hpp"

#include <iostream>

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;

std::ostream& coconut_tools::configuration::hierarchical::operator<<(
	std::ostream& os, const NodeSelector& selector) {
	return os << selector.string();
}
