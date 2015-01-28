#include "DebugWindowAppender.hpp"

#if defined(PLATFORM_WINDOWS)
#	define WIN32_LEAN_AND_MEAN
#	define NOMINMAX
#	include <windows.h>
#endif /* PLATFORM_WINDOWS */

#include "coconut-tools/system/platform.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

const std::string DebugWindowAppender::CLASS_NAME("coconut_tools::logger::appender::DebugWindowAppender");

void DebugWindowAppender::doAppend(const std::string& message) {
#if defined(PLATFORM_WINDOWS)
	OutputDebugString(message.c_str());
#endif /* PLATFORM_WINDOWS */
}
