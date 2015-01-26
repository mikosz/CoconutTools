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
			design_pattern::PermanentStorage,
			design_pattern::NewCreator,
			design_pattern::NoLockingPolicy,
			design_pattern::IgnoringErrorPolicy
			>
{
public:

	AppenderFactory();

};

}  // namespace appender
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_APPENDER_APPENDERFACTORY_HPP_ */
