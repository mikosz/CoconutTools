#ifndef COCONUT_TOOLS_UTILS_HASH_COMBINE_HPP_
#define COCONUT_TOOLS_UTILS_HASH_COMBINE_HPP_

#include <functional>

namespace coconut_tools {
namespace utils {

size_t hashCombine(size_t seed, size_t value) {
	// Code from boost
	// Reciprocal of the golden ratio helps spread entropy and handles duplicates.
	// See Mike Seymour in magic-numbers-in-boosthash-combine: http://stackoverflow.com/questions/4948780
	
	seed ^= std::hash_value(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	return seed;
}

} // namespace utils
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_HASH_COMBINE_HPP_ */
