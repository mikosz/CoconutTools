#include "Selector.hpp"

#include <iostream>

using namespace coconut_tools;
using namespace coconut_tools::configuration;
using namespace coconut_tools::configuration::hierarchical;
using namespace coconut_tools::configuration::hierarchical::node;

std::ostream& coconut_tools::configuration::hierarchical::node::operator<<(
	std::ostream& os, const Selector& selector) {
	return os << selector.string();
}
