#ifndef COCONUT_TOOLS_SYSTEM_SYSTEMERROR_HPP_
#define COCONUT_TOOLS_SYSTEM_SYSTEMERROR_HPP_

#include <cerrno>
#include <cstring>
#include <string>

#include "coconut-tools/exceptions/RuntimeError.hpp"

namespace coconut_tools {
namespace system {

class SystemError : public exceptions::RuntimeError {
public:

    SystemError() :
        exceptions::RuntimeError(constructMessage(std::string())),
        errno_(errno),
        errorString_(std::strerror(errno)) {

    }

    SystemError(const std::string& theMessage) :
        exceptions::RuntimeError(constructMessage(theMessage)),
        errno_(errno),
        errorString_(std::strerror(errno)) {
    }

    ~SystemError() throw() {
    }

    int errNo() const {
        return errno_;
    }

    const std::string& errorString() const {
        return errorString_;
    }

private:

    int errno_;

    std::string errorString_;

    static std::string constructMessage(const std::string& message);

};

}  // namespace system
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_SYSTEM_SYSTEMERROR_HPP_ */
