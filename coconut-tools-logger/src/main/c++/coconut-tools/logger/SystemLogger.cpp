#include "SystemLogger.hpp"

#include "coconut-tools/system/platform.hpp"

#include "layout/EmptyLayout.hpp"
#include "appender/ConsoleAppender.hpp"
#include "appender/DebugWindowAppender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

SystemLogger::SystemLogger() :
	Logger(Level::INFO)
{
	layout::LayoutSharedPtr layout(new layout::EmptyLayout());
	addAppender(std::make_shared<appender::ConsoleAppender>(Level::TRACE, layout));

#if defined(CT_COMPILER_VISUAL_CXX)
	addAppender(std::make_shared<appender::DebugWindowAppender>(Level::TRACE, layout));
#endif /* CT_COMPILER_VISUAL_CXX */
}
