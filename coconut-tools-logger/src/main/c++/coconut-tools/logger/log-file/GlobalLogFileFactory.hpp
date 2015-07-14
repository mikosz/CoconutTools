#ifndef COCONUTTOOLS_LOGGER_LOGFILE_GLOBALLOGFILEFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGFILE_GLOBALLOGFILEFACTORY_HPP_

#include "coconut-tools/design-pattern/singleton.hpp"
#include "LogFileFactory.hpp"

namespace coconut_tools {
namespace logger {
namespace log_file {

class GlobalLogFileFactory :
	public design_pattern::Singleton<
		GlobalLogFileFactory,
		design_pattern::UniqueMutexLockingPolicy,
		design_pattern::NewCreator<GlobalLogFileFactory>
		>,
	public LogFileFactory
{
};

} // namespace log_file
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGFILE_GLOBALLOGFILEFACTORY_HPP_ */
