#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_

#include "exception/RuntimeError.hpp"

namespace coconut_tools {
namespace configuration {

class ConfigurationException : public exception::RuntimeError {
public:

    EXCEPTION_CONSTRUCTORS(ConfigurationException, exception::RuntimeError)

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_ */
