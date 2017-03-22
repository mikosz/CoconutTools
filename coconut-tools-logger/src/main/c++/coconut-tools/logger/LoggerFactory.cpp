#include "LoggerFactory.hpp"

#include "SystemLogger.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

LoggerFactory::LoggerFactory(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration) :
	loggerConfiguration_(loggerConfiguration),
	appenderFactory_(loggerConfiguration)
{
}

void LoggerFactory::reloadConfiguration(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration) {
	storage_.clear();
	loggerConfiguration_ = loggerConfiguration;
	appenderFactory_.reloadConfiguration(loggerConfiguration_);
}

void LoggerFactory::reloadConfiguration(logger::configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration) volatile {
	lock()->reloadConfiguration(loggerConfiguration);
}

LoggerSharedPtr LoggerFactory::create(const LoggerId& loggerId) {
	if (!loggerConfiguration_) {
		return SystemLogger::instance();
	} else {
		return storage_.get(loggerId, [this, &loggerId]() {
				auto logger = std::make_unique<Logger>(loggerConfiguration_->loggerLevel(loggerId));
				for (const auto& appender : loggerConfiguration_->appenderIds(loggerId)) {
					logger->addAppender(appenderFactory_.create(appender));
				}
				return logger;
			});
	}
}

VolatileLoggerSharedPtr LoggerFactory::create(const LoggerId& loggerId) volatile {
	return lock()->create(loggerId);
}
