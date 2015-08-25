#ifndef COCONUTTOOLS_LOGGER_PRINT_HPP_
#define COCONUTTOOLS_LOGGER_PRINT_HPP_

#include <iosfwd>
#include <type_traits>

#include "coconut-tools/utils/IsIterable.hpp"

namespace coconut_tools {
namespace logger {

template<class T>
inline typename std::enable_if_t<!utils::IsIterable<T>::value> print(std::ostream& os, const T& v) {
	os << v;
}

template <class T>
inline typename std::enable_if_t<utils::IsIterable<T>::value> print(std::ostream& os, const T& iterable) {
	using std::begin;
	using std::end;

	auto it = begin(iterable), endIt = end(iterable);

	if (it != endIt) {
		os << *it;
		++it;
	}

	while (it != endIt) {
		os << ", " << *it;
		++it;
	}
}

inline void print(std::ostream& os, const std::string& s) {
	os << s;
}

inline void print(std::ostream& os, const char* s) {
	os << s;
}

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_PRINT_HPP_ */
