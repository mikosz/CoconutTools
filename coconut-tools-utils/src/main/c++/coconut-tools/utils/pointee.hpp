#ifndef COCONUT_TOOLS_UTILS_POINTEE_HPP_
#define COCONUT_TOOLS_UTILS_POINTEE_HPP_

#include "coconut-tools/exceptions/RuntimeError.hpp"

namespace coconut_tools {
namespace utils {

class NullPointerException : public exceptions::RuntimeError {
public:

    NullPointerException() :
        exceptions::RuntimeError("Attempted to dereference a null pointer.") {
    }

    ~NullPointerException() throw () {
    }

};

template <class T>
T& pointee(T* ptr) {
    if (!ptr) {
        throw NullPointerException();
    }
    return *ptr;
}

}  // namespace utils
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_POINTEE_HPP_ */
