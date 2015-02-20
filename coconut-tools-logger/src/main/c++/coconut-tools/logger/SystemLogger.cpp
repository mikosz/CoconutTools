#include "SystemLogger.hpp"

#include "layout/EmptyLayout.hpp"
#include "appender/ConsoleAppender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

SystemLogger::SystemLogger() :
	Logger(Level::INFO)
{
	layout::LayoutSharedPtr layout(new layout::EmptyLayout());
	addAppender(std::make_shared<appender::ConsoleAppender>(layout));
}
