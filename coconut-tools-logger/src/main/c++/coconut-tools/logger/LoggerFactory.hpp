#ifndef COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_

#include "Logger.hpp"
#include "appender/ConsoleAppender.hpp"
#include "layout/EmptyLayout.hpp"

namespace coconut_tools {
namespace logger {

class LoggerFactory {
public:

	Logger& getSystemLogger() const {
		static bool initialised = false;
		static Logger logger(Level::INFO);
		static layout::LayoutPtr layout(new layout::EmptyLayout());
		static appender::AppenderPtr appender(new appender::ConsoleAppender(layout));
		if (!initialised) {
			logger.addAppender(appender);
			initialised = true;
		}

		return logger;
	}

};

}  // namespace logger
}  // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGGERFACTORY_HPP_ */
