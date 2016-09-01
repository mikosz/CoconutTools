#ifndef COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_

#include <string>

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"

#include "coconut-tools/design-pattern/factory/storage/Permanent.hpp"

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

	LoggerFactory(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	void reloadConfiguration(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration);

	void reloadConfiguration(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration) volatile;

	LoggerSharedPtr create(const LoggerId& loggerId);

	VolatileLoggerSharedPtr create(const LoggerId& loggerId) volatile;

	appender::AppenderFactory& appenderFactory() {
		return appenderFactory_;
	}

private:

	configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration_;

	design_pattern::factory::storage::Permanent<LoggerId, LoggerSharedPtr> storage_;

	appender::AppenderFactory appenderFactory_;

};

}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_ */
