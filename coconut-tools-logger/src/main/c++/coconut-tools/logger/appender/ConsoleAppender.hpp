#ifndef COCONUTTOOLS_LOGGER_APPENDER_CONSOLEAPPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_CONSOLEAPPENDER_HPP_

#include "Appender.hpp"

#include <string>
#include <iostream>

#include "coconut-tools/design-pattern/factory/creator/NewCreator.hpp"

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

protected:

	void doAppend(const std::string& message) {
		std::clog << message;
		std::clog.flush();
	}

private:

	ConsoleAppender() {
	}

	friend class design_pattern::factory::creator::NewCreator<Appender>;

};

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_CONSOLEAPPENDER_HPP_ */
