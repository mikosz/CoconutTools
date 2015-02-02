#ifndef COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_
#define COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_

#include "Appender.hpp"

#include "coconut-tools/design-pattern/factory.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class AppenderFactory :
		public design_pattern::factory::Factory<
			Appender::Id,
			Appender,
			design_pattern::PermanentStorage,
			design_pattern::FunctorCreator<Appender>,
			design_pattern::NoLockingPolicy,
			design_pattern::IgnoringErrorPolicy
			>
{
public:

	typedef design_pattern::NewCreator<
		Appender,
		const Appender::Id&,
		const logger::configuration::LoggerConfiguration&,
		layout::LayoutFactory*
		> AppenderCreator;

	AppenderFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	void registerCreator(const Appender::Id& appenderId, AppenderCreator creator);

private:

	typedef design_pattern::factory::Factory<
		Appender::Id,
		Appender,
		design_pattern::PermanentStorage,
		design_pattern::FunctorCreator<Appender>,
		design_pattern::NoLockingPolicy,
		design_pattern::IgnoringErrorPolicy
		> Super;

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

	layout::LayoutFactory layoutFactory_;

};

}  // namespace appender
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_ */
