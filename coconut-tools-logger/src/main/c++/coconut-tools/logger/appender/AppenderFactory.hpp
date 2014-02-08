#ifndef COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_
#define COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_

#include <string>

#include "Appender.hpp"

#include "coconut-tools/design-pattern/factory.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class AppenderFactory :
		public design_pattern::factory::Factory<
			std::string,
			Appender,
			design_pattern::factory::PermanentStorage,
			design_pattern::factory::NewCreator,
			design_pattern::factory::NoLockingPolicy,
			design_pattern::factory::IgnoringErrorPolicy
			>
{
public:

	AppenderFactory();

};

}  // namespace appender
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_ */
