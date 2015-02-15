#ifndef COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_

#include "coconut-tools/system/platform.hpp"

#if defined(COMPILER_VISUAL_CXX)

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

#endif /* COMPILER_VISUAL_CXX */

#endif /* COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_ */
