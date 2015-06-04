#ifndef COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_

#include "coconut-tools/design-pattern/singleton.hpp"

#include "LoggerFactory.hpp"

namespace coconut_tools {
namespace logger {

class GlobalLoggerFactory :
	public design_pattern::Singleton<
		LoggerFactory,
		design_pattern::UniqueMutexLockingPolicy,
		design_pattern::NewCreator<GlobalLoggerFactory>
		>,
	public LoggerFactory
{
public:

	GlobalLoggerFactory();

};

}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_GLOBALLOGGERFACTORY_HPP_ */
