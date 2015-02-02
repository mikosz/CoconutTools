#include "LoggerFactory.hpp"

using namespace coconut_tools::logger;

LoggerFactory::LoggerFactory(configuration::ConstLoggerConfigurationSharedPtr loggerConfiguration) :
	loggerConfiguration_(loggerConfiguration),
	appenderFactory_(loggerConfiguration)
{
}

LoggerSharedPtr LoggerFactory::create(const LoggerId& loggerId) {
	LoggerSharedPtr logger = storage_.get(loggerId);
	if (logger) {
		return logger;
	}
	
	LoggerUniquePtr newLogger(new Logger(loggerConfiguration_->loggerLevel(loggerId)));
	newLogger->addAppender(appenderFactory_.create(loggerId));
	return storage_.store(loggerId, LoggerUniquePtr(newLogger.release()));
}

VolatileLoggerSharedPtr LoggerFactory::create(const LoggerId& loggerId) volatile {
	return lock()->create(loggerId);
}
