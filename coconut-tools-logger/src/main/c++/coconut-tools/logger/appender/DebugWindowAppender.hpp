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

	DebugWindowAppender(const Id& id, layout::LayoutPtr layout) :
		Appender(id, layout)
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

	void doAppend(const std::string& message);

private:

	friend class design_pattern::creator::NewCreator<Appender>;

};

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_ */
