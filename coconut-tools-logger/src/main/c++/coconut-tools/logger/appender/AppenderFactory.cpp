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

	factory.registerType<ConsoleAppender>(ConsoleAppender::CLASS_NAME);
	factory.registerType<FileAppender>(FileAppender::CLASS_NAME);
	factory.registerType<DebugWindowAppender>(DebugWindowAppender::CLASS_NAME);
}

} // anonymous namespace

AppenderFactory::AppenderFactory(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration) :
	loggerConfiguration_(loggerConfiguration),
	layoutFactory_(loggerConfiguration)
{
	registerBuiltins(this);
}

AppenderSharedPtr AppenderFactory::create(const Appender::Id& appenderId) {
	if (instanceStorage_.isStored(appenderId)) {
		return instanceStorage_.get(appenderId);
	}

	auto initialiser = typeFactory_.create(loggerConfiguration_->appenderTypeId(appenderId));
	instanceStorage_.store(appenderId, initialiser->initialise(appenderId, *loggerConfiguration_, &layoutFactory_));
	return instanceStorage_.get(appenderId);
}
