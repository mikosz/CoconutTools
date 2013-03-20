#ifndef COCONUT_TOOLS_EXCEPTIONS_RUNTIMEERROR_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_RUNTIMEERROR_HPP_

#include <stdexcept>

#include "GenericException.hpp"

namespace coconut_tools {
namespace exceptions {

class RuntimeError : public GenericException<std::runtime_error> {
public:

    EXCEPTION_CONSTRUCTORS(RuntimeError, GenericException<std::runtime_error>)

};

} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_RUNTIMEERROR_HPP_ */
