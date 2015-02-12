#ifndef COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_

#include "Appender.hpp"

#include <string>

#include "coconut-tools/design-pattern/creator/NewCreator.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class DebugWindowAppender : public Appender {
public:

	static const std::string CLASS_NAME;

	DebugWindowAppender(layout::LayoutPtr layout) :
		Appender(layout)
	{
	}

	DebugWindowAppender(
		const Id& id,
		const logger::configuration::LoggerConfiguration& configuration,
		layout::LayoutFactory* layoutFactory
		) :
		Appender(id, configuration, layoutFactory)
	{
	}

protected:

	void doAppend(const std::string& message) override;

private:

	DebugWindowAppender() {
	}

	friend class Initialiser;

};

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_ */
