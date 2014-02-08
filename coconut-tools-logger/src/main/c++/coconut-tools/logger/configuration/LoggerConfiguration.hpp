#ifndef LOGGERCONFIGURATION_HPP_
#define LOGGERCONFIGURATION_HPP_

#include <boost/shared_ptr.hpp>

namespace coconut_tools {
namespace logger {
namespace configuration {

class LoggerConfiguration {
public:

	virtual ~LoggerConfiguration() {
	}

private:

};

typedef boost::shared_ptr<LoggerConfiguration> LoggerConfigurationPtr;
typedef boost::shared_ptr<const LoggerConfiguration> ConstLoggerConfigurationPtr;

}  // namespace configuration
}  // namespace logger
}  // namespace coconut_tools

#endif /* LOGGERCONFIGURATION_HPP_ */
