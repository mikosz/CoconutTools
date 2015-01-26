#ifndef COCONUTTOOLS_LOGGER_SYSTEMLOGGER_HPP_
#define COCONUTTOOLS_LOGGER_SYSTEMLOGGER_HPP_

#include "coconut-tools/design-pattern/singleton.hpp"

#include "Logger.hpp"

namespace coconut_tools {
namespace logger {

class SystemLogger :
	public design_pattern::Singleton<
		Logger,
		design_pattern::UniqueMutexLockingPolicy,
		design_pattern::NewCreator<SystemLogger>
		>,
	public Logger
{
public:

	SystemLogger();

};

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_SYSTEMLOGGER_HPP_ */
