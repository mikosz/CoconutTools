#ifndef COCONUT_TOOLS_SYSTEM_SYSTEMERROR_HPP_
#define COCONUT_TOOLS_SYSTEM_SYSTEMERROR_HPP_

#include <system_error>

#include "coconut-tools/exceptions/RuntimeError.hpp"

namespace coconut_tools {
namespace system {

class SystemError : public exceptions::RuntimeError {
public:

    SystemError(const std::error_code& theErrorCode) :
        exceptions::RuntimeError(constructMessage(std::string(), theErrorCode)),
		errorCode_(theErrorCode)
	{
    }

    SystemError(const std::string& theMessage, const std::error_code& theErrorCode) :
        exceptions::RuntimeError(constructMessage(theMessage, theErrorCode))
	{
    }

    ~SystemError() throw() {
    }

	const std::error_code& errorCode() {
		return errorCode_;
	}

private:

	std::error_code errorCode_;

    static std::string constructMessage(const std::string& message, const std::error_code& theErrorCode);

};

}  // namespace system
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_SYSTEM_SYSTEMERROR_HPP_ */
