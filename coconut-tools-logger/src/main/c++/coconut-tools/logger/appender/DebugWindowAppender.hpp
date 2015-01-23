#ifndef COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_

#include "Appender.hpp"

#include <string>

#include "coconut-tools/design-pattern/factory/creator/NewCreator.hpp"

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

protected:

	void doAppend(const std::string& message);

private:

	DebugWindowAppender() {
	}

	friend class design_pattern::factory::creator::NewCreator<Appender>;

};

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_DEBUGWINDOWAPPENDER_HPP_ */
