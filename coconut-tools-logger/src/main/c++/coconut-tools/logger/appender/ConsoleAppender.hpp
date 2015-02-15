#ifndef COCONUTTOOLS_LOGGER_APPENDER_CONSOLEAPPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_CONSOLEAPPENDER_HPP_

#include "Appender.hpp"

#include <string>
#include <iostream>

#include "coconut-tools/design-pattern/creator/NewCreator.hpp"

#include "coconut-tools/logger/configuration/LoggerConfiguration.hpp"
#include "coconut-tools/logger/layout/LayoutFactory.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class ConsoleAppender : public Appender {
public:

	static const std::string CLASS_NAME;

	ConsoleAppender(layout::LayoutPtr layout) :
		Appender(layout)
	{
	}

	ConsoleAppender(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactory
		) :
		Appender(id, configuration, layoutFactory)
	{
	}

protected:

	void doAppend(const std::string& message) override {
		std::clog << message;
		std::clog.flush();
	}

private:

	ConsoleAppender() {
	}

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

#endif /* COCONUTTOOLS_LOGGER_APPENDER_CONSOLEAPPENDER_HPP_ */
