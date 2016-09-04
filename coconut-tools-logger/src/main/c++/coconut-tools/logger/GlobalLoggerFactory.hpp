#ifndef COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_

#include <boost/thread/mutex.hpp>

#include <boost/filesystem/path.hpp>

#include "coconut-tools/singleton.hpp"

#include "LoggerFactory.hpp"

namespace coconut_tools {
namespace logger {

class GlobalLoggerFactory :
	public Singleton<
		GlobalLoggerFactory,
		boost::mutex,
		policy::creation::New<GlobalLoggerFactory>
		>,
	public LoggerFactory
{
public:

	static const boost::filesystem::path& defaultConfigurationPath();

	GlobalLoggerFactory();

	using LoggerFactory::reloadConfiguration;

	void reloadConfiguration(const boost::filesystem::path& path = defaultConfigurationPath());

	void reloadConfiguration(const boost::filesystem::path& path = defaultConfigurationPath()) volatile;

private:

	static const boost::filesystem::path DEFAULT_CONFIGURATION_PATH;

};

}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_ */
