#include "Appender.hpp"

#include "coconut-tools/utils/pointee.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

Appender::Appender(
	const Id& id,
	const logger::configuration::LoggerConfiguration& configuration,
	layout::LayoutFactory* layoutFactoryPtr
	)
{
	doInitialise(id, configuration, layoutFactoryPtr);
}

void Appender::doInitialise(
	const Id& id,
	const logger::configuration::LoggerConfiguration& configuration,
	layout::LayoutFactory* layoutFactoryPtr
	) {
	layout::LayoutFactory& layoutFactory = utils::pointee(layoutFactoryPtr);

	layout_ = layoutFactory.create(configuration.layoutId(id));
}

void Appender::append(Level level, const Context& context, const std::string& message) {
	doAppend(layout_->format(level, context, message));
}
