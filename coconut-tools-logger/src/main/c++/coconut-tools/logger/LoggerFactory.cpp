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
		auto appenders = loggerConfiguration_->appenderIds(loggerId);
		for (auto appender : appenders) {
			newLogger->addAppender(appenderFactory_.create(appender));
		}
		return storage_.store(loggerId, LoggerUniquePtr(newLogger.release()));
	}
}

VolatileLoggerSharedPtr LoggerFactory::create(const LoggerId& loggerId) volatile {
	auto locked = lock();

	auto logger = locked->storage_.get(loggerId);
	if (logger) {
		return logger;
	}

	VolatileLoggerUniquePtr newLogger(new Logger(locked->loggerConfiguration_->loggerLevel(loggerId)));
	newLogger->addAppender(appenderFactory_.create(locked->loggerConfiguration_->appenderId(loggerId)));
	return locked->volatileStorage_.store(loggerId, std::move(newLogger));
}
