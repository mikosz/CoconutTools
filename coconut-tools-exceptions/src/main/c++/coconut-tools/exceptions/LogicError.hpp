#ifndef COCONUT_TOOLS_EXCEPTIONS_LOGICERROR_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_LOGICERROR_HPP_

#include <stdexcept>

#include "GenericException.hpp"

namespace coconut_tools {
namespace exceptions {

class LogicError : public GenericException<std::logic_error> {
public:

    EXCEPTION_CONSTRUCTORS(LogicError, GenericException<std::logic_error>)

};

} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_LOGICERROR_HPP_ */
