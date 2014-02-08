#ifndef COCONUT_TOOLS_LAYOUT_LAYOUTFACTORY_HPP_
#define COCONUT_TOOLS_LAYOUT_LAYOUTFACTORY_HPP_

#include <string>

#include "Layout.hpp"

#include "coconut-tools/design-pattern/factory.hpp"
#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class LayoutFactory :
		public design_pattern::factory::Factory<
			std::string,
			Layout,
			design_pattern::factory::PermanentStorage,
			design_pattern::factory::NewCreator,
			design_pattern::factory::NoLockingPolicy,
			design_pattern::factory::IgnoringErrorPolicy
			>
{
public:

	LayoutFactory(configuration::ConstLoggerConfigurationPtr loggerConfiguration);

private:

	configuration::ConstLoggerConfigurationPtr loggerConfiguration_;

};

}  // namespace layout
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_LAYOUT_LAYOUTFACTORY_HPP_ */
