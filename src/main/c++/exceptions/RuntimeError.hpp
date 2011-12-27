#ifndef COCONUT_TOOLS_EXCEPTIONS_RUNTIMEERROR_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_RUNTIMEERROR_HPP_

#include <stdexcept>

#include "Exception.hpp"

namespace coconut_tools {
namespace exceptions {

class RuntimeError : public Exception, public std::runtime_error {
public:

    RuntimeError() :
        Exception(),
        std::runtime_error(message()) {
    }

    RuntimeError(const std::string& theMessage) :
        Exception(theMessage),
        std::runtime_error(message()) {
    }

    RuntimeError(const std::string& theMessage, const std::exception& cause) :
        Exception(theMessage, cause),
        std::runtime_error(message()) {
    }

    ~RuntimeError() throw() {
    }

    const char* what() const throw() {
        return description().c_str();
    }

    const std::string& name() const {
        static const std::string NAME = "RuntimeError";
        return NAME;
    }

};

} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_RUNTIMEERROR_HPP_ */
