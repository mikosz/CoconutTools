#ifndef COCONUT_TOOLS_UTILS_TO_STRING_HPP_
#define COCONUT_TOOLS_UTILS_TO_STRING_HPP_

#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace utils {

template <class T>
std::string toString(const typename boost::call_traits<T>::param_type value) {
    try {
        return boost::lexical_cast<std::string>(value);
    } catch (const boost::bad_lexical_cast&) {
        std::ostringstream oss;
        oss << typeid(T).name() << "[" << &value << "]";
        return oss.str();
    }
}

}  // namespace utils
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_TO_STRING_HPP_ */
