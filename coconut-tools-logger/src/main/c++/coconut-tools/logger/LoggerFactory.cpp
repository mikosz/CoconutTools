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
		LoggerSharedPtr logger = storage_.get(loggerId);
		if (logger) {
			return logger;
		}

		LoggerUniquePtr newLogger(new Logger(loggerConfiguration_->loggerLevel(loggerId)));
		newLogger->addAppender(appenderFactory_.create(loggerConfiguration_->appenderId(loggerId)));
		return storage_.store(loggerId, LoggerUniquePtr(newLogger.release()));
	}
}

VolatileLoggerSharedPtr LoggerFactory::create(const LoggerId& loggerId) volatile {
	return lock()->create(loggerId);
}
