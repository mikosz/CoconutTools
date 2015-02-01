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

AppenderFactory::AppenderFactory(logger::configuration::ConstLoggerConfigurationPtr loggerConfiguration) :
	loggerConfiguration_(loggerConfiguration),
	layoutFactory_(loggerConfiguration)
{
	registerBuiltins(*this);
}

void AppenderFactory::registerCreator(const Appender::Id& appenderId, AppenderCreator creator) {
	Super::registerCreator(
		appenderId,
		design_pattern::FunctorCreator<Appender>(
			[=, &creator]() { creator.create(appenderId, this->loggerConfiguration_, &this->layoutFactory_); }
			)
		);
}
