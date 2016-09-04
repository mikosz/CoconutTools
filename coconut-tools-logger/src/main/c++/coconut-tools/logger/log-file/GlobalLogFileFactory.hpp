#ifndef COCONUTTOOLS_LOGGER_LOGFILE_GLOBALLOGFILEFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGFILE_GLOBALLOGFILEFACTORY_HPP_

#include <boost/thread/mutex.hpp>

#include "coconut-tools/policy/creation/New.hpp"

#include "coconut-tools/singleton.hpp"

#include "LogFileFactory.hpp"

namespace coconut_tools {
namespace logger {
namespace log_file {

class GlobalLogFileFactory :
	public Singleton<
		GlobalLogFileFactory,
		boost::mutex,
		policy::creation::New<GlobalLogFileFactory>
		>,
	public LogFileFactory
{
};

} // namespace log_file
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGFILE_GLOBALLOGFILEFACTORY_HPP_ */
