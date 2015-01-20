#include "Appender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

void Appender::append(Level level, const Context& context, const std::string& message) {
	doAppend(layout_->format(level, context, message));
}
