#include "AppenderFactory.hpp"

#include "ConsoleAppender.hpp"
#include "DebugWindowAppender.hpp"
#include "FileAppender.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

namespace {

void registerBuiltins(AppenderFactory& factory) {
	factory.registerCreator(
		ConsoleAppender::CLASS_NAME, 
		AppenderFactory::AppenderCreator::makeCreator<ConsoleAppender>()
		);
	factory.registerCreator(
		DebugWindowAppender::CLASS_NAME,
		AppenderFactory::AppenderCreator::makeCreator<DebugWindowAppender>()
		);
	factory.registerCreator(
		FileAppender::CLASS_NAME,
		AppenderFactory::AppenderCreator::makeCreator<FileAppender>()
		);
}

} // anonymous namespace

AppenderFactory::AppenderFactory(configuration::ConstLoggerConfigurationPtr loggerConfiguration) :
	loggerConfiguration_(loggerConfiguration),
	layoutFactory_(loggerConfiguration)
{
	registerBuiltins(*this);
}

void AppenderFactory::registerCreator(const std::string& appenderId, AppenderCreator creator) {
	Super::registerCreator(appenderId, [=]() { creator(loggerConfiguration_, layoutFactory_); });
}
