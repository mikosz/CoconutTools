#include "FileAppender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

const std::string FileAppender::CLASS_NAME("coconut_tools::logger::appender::FileAppender");

void FileAppender::doInitialise(
	const Id& id,
	const logger::configuration::LoggerConfiguration& configuration,
	layout::LayoutFactory* layoutFactoryPtr
	) {
	layout::LayoutFactory& layoutFactory = utils::pointee(layoutFactoryPtr);

	// TODO: initialise log file
}