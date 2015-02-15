#ifndef COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_

#include <string>

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"

#include "coconut-tools/design-pattern/factory/storage/PermanentStorage.hpp"

#include "coconut-tools/concurrent/Lockable.hpp"

#include "appender/ConsoleAppender.hpp"
#include "appender/AppenderFactory.hpp"
#include "layout/LayoutFactory.hpp"
#include "Logger.hpp"

namespace coconut_tools {
namespace logger {

class LoggerFactory : public concurrent::Lockable<LoggerFactory> {
public:

	typedef std::string LoggerId;

	LoggerFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	LoggerSharedPtr create(const LoggerId& loggerId);

	VolatileLoggerSharedPtr create(const LoggerId& loggerId) volatile;

private:

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

	design_pattern::factory::storage::PermanentStorage<LoggerId, LoggerSharedPtr> storage_;

	appender::AppenderFactory appenderFactory_;

};

}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_ */
