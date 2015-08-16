#ifndef COCONUTTOOLS_LOGGER_PRINT_HPP_
#define COCONUTTOOLS_LOGGER_PRINT_HPP_

#include <iosfwd>
#include <type_traits>

#include "coconut-tools/utils/IsIterable.hpp"

namespace coconut_tools {
namespace logger {

template<class T>
typename std::enable_if<!utils::IsIterable<T>::value, void>::type
	print(std::ostream& os, const T& v) {
	os << v;
}

/* template <class T>
typename std::enable_if<utils::IsIterable<T>::value, void>::type
	print(std::ostream& os, const T& iterable) {
	using std::begin;
	using std::end;

	auto it = begin(iterable), endIt = end(iterable);

	if (it != endIt) {
		oss_ << *it;
		++it;
	}

	while (it != endIt) {
		oss_ << ", " << *it;
		++it;
	}
} */

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_PRINT_HPP_ */
