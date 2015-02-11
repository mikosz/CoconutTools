#ifndef COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_
#define COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_

#include "Appender.hpp"

#include "coconut-tools/design-pattern/factory.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class AppenderFactory {
public:

	typedef std::string AppenderTypeId;

	typedef design_pattern::NewCreator<
		Appender,
		const Appender::Id&,
		const logger::configuration::LoggerConfiguration&,
		layout::LayoutFactory*
		> AppenderCreator;

	AppenderFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	void registerCreator(const AppenderTypeId& appenderTypeId, AppenderCreator creator);

	AppenderSharedPtr create(const Appender::Id& appenderId);

private:

	typedef design_pattern::factory::Factory<
		AppenderTypeId,
		Appender,
		design_pattern::NoStorage,
		design_pattern::FunctorCreator<Appender>,
		design_pattern::NoLockingPolicy,
		design_pattern::ExceptionThrowingErrorPolicy
		> AppenderTypeFactory;

	AppenderTypeFactory typeFactory_;

	design_pattern::PermanentStorage<Appender::Id, Appender> instanceStorage_;

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

	layout::LayoutFactory layoutFactory_;

};

}  // namespace appender
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_ */
