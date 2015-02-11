#include "AppenderFactory.hpp"

#include "ConsoleAppender.hpp"
#include "DebugWindowAppender.hpp"
#include "FileAppender.hpp"

#include "coconut-tools/utils/pointee.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::appender;

namespace {

void registerBuiltins(AppenderFactory* factoryPtr) {
	AppenderFactory& factory = utils::pointee(factoryPtr);

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

AppenderFactory::AppenderFactory(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration) :
	loggerConfiguration_(loggerConfiguration),
	layoutFactory_(loggerConfiguration)
{
	registerBuiltins(this);
}

void AppenderFactory::registerCreator(const AppenderTypeId& appenderTypeId, AppenderCreator creator) {
	typeFactory_.registerCreator(
		appenderTypeId,
		design_pattern::FunctorCreator<Appender>( // TODO: I couldn't replace this with a lambda - why?
			std::bind(&AppenderCreator::create, creator, appenderTypeId, std::cref(*loggerConfiguration_), &layoutFactory_)
			)
		);
}

AppenderSharedPtr AppenderFactory::create(const Appender::Id& appenderId) {
	if (instanceStorage_.isStored(appenderId)) {
		return instanceStorage_.get(appenderId);
	}

	instanceStorage_.store(appenderId, typeFactory_.create(loggerConfiguration_->appenderTypeId(appenderId)));
	return instanceStorage_.get(appenderId);
}
