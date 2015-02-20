#include "coconut-tools/system/platform.hpp"

#if defined(COMPILER_VISUAL_CXX)

#include "DebugWindowAppender.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "coconut-tools/system/platform.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

const std::string DebugWindowAppender::CLASS_NAME("coconut_tools::logger::appender::DebugWindowAppender");

void DebugWindowAppender::doAppend(const std::string& message) {
	OutputDebugString(message.c_str());
}

#endif /* COMPILER_VISUAL_CXX */
