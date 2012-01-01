#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_

#include "exceptions/RuntimeError.hpp"

namespace coconut_tools {
namespace configuration {

class ConfigurationException : public exceptions::RuntimeError {
public:

    EXCEPTION_CONSTRUCTORS(ConfigurationException, exceptions::RuntimeError)

};

class MissingRequiredValue : public ConfigurationException {
public:

    MissingRequiredValue(const std::string& theKey) :
        ConfigurationException(constructMessage(theKey)),
        key_(theKey) {
    }

    ~MissingRequiredValue() throw() {
    }

    const std::string& key() const {
        return key_;
    }

private:

    std::string key_;

    static std::string constructMessage(const std::string& key);

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_ */
