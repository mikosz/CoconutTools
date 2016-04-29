#include "Context.hpp"

using namespace coconut_tools::logger;

const Context Context::EMPTY;

const Context& Context::empty() {
	return EMPTY;
}
