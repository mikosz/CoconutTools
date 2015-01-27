#ifndef COCONUT_TOOLS_LOGGER_LOGGERCONFIGURATION_HPP_
#define COCONUT_TOOLS_LOGGER_LOGGERCONFIGURATION_HPP_

#include <memory>

namespace coconut_tools {
namespace logger {
namespace configuration {

class LoggerConfiguration {
public:

	virtual ~LoggerConfiguration() {
	}

private:

};

typedef std::shared_ptr<LoggerConfiguration> LoggerConfigurationPtr;
typedef std::shared_ptr<const LoggerConfiguration> ConstLoggerConfigurationPtr;

}  // namespace configuration
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_LOGGER_LOGGERCONFIGURATION_HPP_ */
