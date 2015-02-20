#ifndef COCONUT_TOOLS_EXCEPTIONS_GENERICEXCEPTION_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_GENERICEXCEPTION_HPP_

#include <string>
#include <sstream>
#include <exception>

#include "Backtrace.hpp"

namespace coconut_tools {
namespace exceptions {

template <class ParentType>
class GenericException : public ParentType {
public:

    GenericException(const std::string& message) :
        ParentType(message),
        message_(message) {
    }

    GenericException(const std::string& message, const std::exception& cause) :
        ParentType(message),
        message_(message),
        cause_(cause.what()) {
    }

    virtual ~GenericException() throw () {
    }

    virtual const std::string& name() const = 0;

    const char* what() const throw () {
        return description().c_str();
    }

    const std::string& message() const {
        return message_;
    }

    const Backtrace& backtrace() const {
        return backtrace_;
    }

    const std::string& description() const {
        // description_ is built lazily, because we're calling name() which is virtual and
        // cannot be called in the constructor
        if (description_.empty()) {
            std::ostringstream oss;
            oss << name();
            if (!message_.empty()) {
                oss << "\nMessage: " << message_;
            }
            oss << '\n' << backtrace_;
            if (!cause_.empty()) {
                oss << "\nCaused by: " << cause_;
            }
            description_ = oss.str();
        }
        return description_;
    }

private:

    std::string message_, cause_;

    mutable std::string description_;

    Backtrace backtrace_;

};

#define EXCEPTION_CONSTRUCTORS(TYPE, PARENT) \
    TYPE() : \
        PARENT(#TYPE) { \
    } \
    \
    TYPE(const std::string& message) : \
        PARENT(message) { \
    } \
    \
    TYPE(const std::string& message, const std::exception& cause) : \
        PARENT(message, cause) { \
    } \
    \
    const std::string& name() const { \
        static const std::string& NAME = #TYPE; \
        return NAME; \
    }

} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_GENERICEXCEPTION_HPP_ */
