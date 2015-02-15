#ifndef COCONUTTOOLS_LOGGER_APPENDER_FILEAPPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_FILEAPPENDER_HPP_

#include <fstream>
#include <string>

#include "Appender.hpp"

#include "coconut-tools/design-pattern/creator/NewCreator.hpp"

#include "coconut-tools/utils/pointee.hpp"

#include "coconut-tools/logger/log-file/LogFile.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class FileAppender : public Appender {
public:

	static const std::string CLASS_NAME;

	FileAppender(layout::LayoutPtr layout, log_file::LogFileSharedPtr logFile) :
		Appender(layout),
		logFile_(logFile)
	{
	}

	FileAppender(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactoryPtr
		) :
		Appender(id, configuration, layoutFactoryPtr)
	{
		layout::LayoutFactory& layoutFactory = utils::pointee(layoutFactoryPtr);
		doInitialise(id, configuration, &layoutFactory);
	}

protected:

	void doAppend(const std::string& message) override {
		return logFile_->write(message);
	}

	void doInitialise(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactory
		) override;

private:

	FileAppender() {
	}

	log_file::LogFileSharedPtr logFile_;

	friend class utils::Initialiser<
		Appender,
		const Id&,
		const logger::configuration::LoggerConfiguration&,
		layout::LayoutFactory*
		>;

};

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_FILEAPPENDER_HPP_ */
