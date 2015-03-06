#ifndef COCONUT_TOOLS_LOGGER_LOGGERCONFIGURATION_HPP_
#define COCONUT_TOOLS_LOGGER_LOGGERCONFIGURATION_HPP_

#include <memory>
#include <string>

#include "coconut-tools/configuration/hierarchical/HierarchicalConfiguration.hpp"

#include "coconut-tools/exceptions/RuntimeError.hpp"

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

#include "coconut-tools/logger/Level.hpp"

namespace coconut_tools {
namespace logger {
namespace configuration {

class LoggerConfigurationError : public exceptions::RuntimeError {
public:

	LoggerConfigurationError(const std::string& message) :
		exceptions::RuntimeError(message)
	{
	}

};

/**
 * <pre>
 *   <root-logger>
 *     <level>INFO</level>
 *   </root-logger>
 *   <loggers>
 *     <logger>
 *       <id>logger-id</id>
 *       <level>DEBUG</level>
 *       <appender-ids>
 *         <appender-id>console-appender</appender-id>
 *         <appender-id>file-appender</appender-id>
 *       </appender-ids>
 *     </logger>
 *     <logger>
 *       <id>logger-id.child</id>
 *       <level>INFO</level>
 *     </logger>
 *   </loggers>
 *   <appenders>
 *     <appender>
 *       <id>console-appender</id>
 *       <type>coconut_tools::logger::appender::ConsoleAppender</type>
 *       <layout-id>layout-id</layout-id>
 *     </appender>
 *     <appender>
 *       <id>file-appender</id>
 *       <type>coconut_tools::logger::appender::FileAppender</type>
 *       <configuration>
 *         <log-file-id>file-id</log-file-id>
 *         <layout-id>layout-id</layout-id>
 *       </configuration>
 *     </appender>
 *     <layouts>
 *       <layout>
 *         <id>layout-id</id>
 *         <type>coconut_tools::logger::layout::EmptyLayout</type>
 *       </layout>
 *     </layouts>
 *     <log-files>
 *       <log-file>
 *         <id>file-id</id>
 *         <path>path/to/a/log/file.log</path>
 *         <overwrite>false</overwrite>
 *       </log-file>
 *     </log-files>
 * </pre>
 */
class LoggerConfiguration {
public:

	typedef std::string LoggerId;

	typedef std::string AppenderId;

	typedef std::string AppenderTypeId;

	typedef std::string LayoutId;

	typedef coconut_tools::configuration::hierarchical::ConstHierarchicalConfigurationSharedPtr Configuration;

	LoggerConfiguration(Configuration config) :
		configuration_(config)
	{
	}

	virtual ~LoggerConfiguration() {
	}

	Level loggerLevel(const LoggerId& loggerId) const;

	Level appenderLevel(const AppenderId& appenderId) const;

	AppenderId appenderId(const LoggerId& loggerId) const;

	LayoutId layoutId(const AppenderId& appenderId) const;

	AppenderTypeId appenderTypeId(const AppenderId& appenderId) const;

	LayoutId layoutTypeId(const LayoutId& layoutId) const;

	Configuration layoutConfiguration(const LayoutId& layoutId) const;

private:

	Configuration configuration_;

};

CT_SMART_POINTER_DEFINITONS(LoggerConfiguration);

}  // namespace configuration
}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_LOGGER_LOGGERCONFIGURATION_HPP_ */
