#ifndef COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_

#include <boost/filesystem/path.hpp>

#include "coconut-tools/design-pattern/singleton.hpp"

#include "LoggerFactory.hpp"

namespace coconut_tools {
namespace logger {

class GlobalLoggerFactory :
	public design_pattern::Singleton<
		GlobalLoggerFactory,
		design_pattern::UniqueMutexLockingPolicy,
		design_pattern::NewCreator<GlobalLoggerFactory>
		>,
	public LoggerFactory
{
public:

	static const boost::filesystem::path DEFAULT_CONFIGURATION_PATH;

	GlobalLoggerFactory();

	using LoggerFactory::reloadConfiguration;

	void reloadConfiguration(const boost::filesystem::path& path = DEFAULT_CONFIGURATION_PATH);

	void reloadConfiguration(const boost::filesystem::path& path = DEFAULT_CONFIGURATION_PATH) volatile;

};

}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_ */
