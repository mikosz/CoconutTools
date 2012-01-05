#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_

#include <boost/call_traits.hpp>

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

class MultipleValuesWhereSingleValueRequired : public ConfigurationException {
public:

    MultipleValuesWhereSingleValueRequired(const std::string& theKey) :
        ConfigurationException(constructMessage(theKey)),
        key_(theKey) {
    }

    ~MultipleValuesWhereSingleValueRequired() throw() {
    }

    const std::string& key() const {
        return key_;
    }

private:

    std::string key_;

    static std::string constructMessage(const std::string& key);

};

class ConfigurationValueNotUpdateable : public ConfigurationException {
public:

    ConfigurationValueNotUpdateable(const std::string& theKey,
            const std::string& theOldValue,
            const std::string& theNewValue) :
            ConfigurationException(constructMessage(theKey, theOldValue, theNewValue)),
            key_(theKey),
            oldValue_(theOldValue),
            newValue_(theNewValue) {
    }

    ~ConfigurationValueNotUpdateable() throw() {
    }

    const std::string& key() const {
        return key_;
    }

    const std::string& oldValue() const {
        return oldValue_;
    }

    const std::string& newValue() const {
        return newValue_;
    }

private:

    std::string key_;

    std::string oldValue_;

    std::string newValue_;

    static std::string constructMessage(const std::string& key, const std::string& oldValue,
            const std::string& newValue);

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_EXCEPTIONS_HPP_ */
