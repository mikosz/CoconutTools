#ifndef COCONUT_TOOLS_UTILS_LOCALTIMETHREADSAFE_HPP_
#define COCONUT_TOOLS_UTILS_LOCALTIMETHREADSAFE_HPP_

#include <ctime>
#include <mutex>

#include "coconut-tools/exceptions/LogicError.hpp"

#include "coconut-tools/system/platform.hpp"

#include "coconut-tools/utils/pointee.hpp"

namespace coconut_tools {
namespace utils {

void localtime(std::tm* tmPtr, std::time_t t) {
	std::tm& tm = pointee(tmPtr);

#if defined(CT_COMPILER_VISUAL_CXX)
	if (localtime_s(&tm, &t) != 0) {
		throw exceptions::LogicError("Failed to retrieve localtime");
	}
#else
	static std::mutex localtimeMutex;
	std::unique_lock<std::mutex> localtimeLock(localtimeMutex);

	auto result = std::localtime(&t);
	if (!result) {
		throw exceptions::LogicError("Failed to retrieve localtime");
	}

	tm = *result;
#endif /* CT_COMPILER_VISUAL_CXX */
}

} // namespace utils
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_LOCALTIMETHREADSAFE_HPP_ */
