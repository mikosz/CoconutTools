#ifndef COCONUTTOOLS_LOGGER_APPENDER_FILEAPPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_FILEAPPENDER_HPP_

#include <fstream>
#include <string>

#include "Appender.hpp"

#include "coconut-tools/design-pattern/creator/NewCreator.hpp"
#include "coconut-tools/logger/log-file/LogFile.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class FileAppender : public Appender {
public:

	static const std::string CLASS_NAME;

	FileAppender(const Id& id, layout::LayoutPtr layout, log_file::LogFileSharedPtr logFile) :
		Appender(id, layout),
		logFile_(logFile)
	{
	}

	FileAppender(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactory
		) :
		Appender(id, configuration, layoutFactory)
	{
	}

protected:

	void doAppend(const std::string& message) {
		return logFile_->write(message);
	}

private:

	log_file::LogFileSharedPtr logFile_;

	friend class design_pattern::creator::NewCreator<Appender>;

};

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_FILEAPPENDER_HPP_ */
