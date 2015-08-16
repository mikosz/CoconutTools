#ifndef COCONUT_TOOLS_IS_ITERABLE_HPP_
#define COCONUT_TOOLS_IS_ITERABLE_HPP_

#include <iterator>

namespace coconut_tools {
namespace utils {

namespace detail {

using std::begin;
using std::end;

template <typename T>
auto IsIterable(int) -> decltype(
	begin(std::declval<T&>()) != end(std::declval<T&>()), // begin/end and operator !=
	++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
	*begin(std::declval<T&>()), // operator*
	std::true_type()
);

template <typename T>
std::false_type IsIterable(...);

} // namespace detail

template <typename T>
using IsIterable = decltype(detail::IsIterable<T>(0));

} // namespace utils
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_IS_ITERABLE_HPP_ */
