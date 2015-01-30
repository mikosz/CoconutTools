#include "Appender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

Appender::Appender(
	const logger::configuration::LoggerConfiguration& configuration,
	layout::LayoutFactory* layoutFactory
	) :
	layout_(layoutFactory->create(configuration))
{
}

void Appender::append(Level level, const Context& context, const std::string& message) {
	doAppend(layout_->format(level, context, message));
}
