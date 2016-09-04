#ifndef COCONUTTOOLS_LOGGER_SYSTEMLOGGER_HPP_
#define COCONUTTOOLS_LOGGER_SYSTEMLOGGER_HPP_

#include <boost/thread/mutex.hpp>

#include "coconut-tools/policy/creation/New.hpp"

#include "coconut-tools/singleton.hpp"

#include "Logger.hpp"

namespace coconut_tools {
namespace logger {

class SystemLogger :
	public Singleton<
		Logger,
		boost::mutex,
		policy::creation::New<SystemLogger>
		>,
	public Logger
{
public:

	SystemLogger();

};

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_SYSTEMLOGGER_HPP_ */
