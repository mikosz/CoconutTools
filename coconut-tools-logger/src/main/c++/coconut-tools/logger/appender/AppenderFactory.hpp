#ifndef COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_
#define COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_

#include <string>

#include "Appender.hpp"

#include "coconut-tools/design-pattern/factory.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class AppenderFactory :
		public design_pattern::factory::Factory<
			std::string,
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
		configuration::ConstLoggerConfigurationPtr,
		layout::LayoutFactory&
		> AppenderCreator;

	AppenderFactory(configuration::ConstLoggerConfigurationPtr loggerConfiguration);

	void registerCreator(const std::string& appenderId, AppenderCreator creator);

private:

	typedef design_pattern::factory::Factory<
		std::string,
		Appender,
		design_pattern::PermanentStorage,
		design_pattern::FunctorCreator<Appender>,
		design_pattern::NoLockingPolicy,
		design_pattern::IgnoringErrorPolicy
		> Super;

	configuration::ConstLoggerConfigurationPtr loggerConfiguration_;

	layout::LayoutFactory layoutFactory_;

};

}  // namespace appender
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_ */
