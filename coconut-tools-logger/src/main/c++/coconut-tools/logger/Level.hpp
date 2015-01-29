#ifndef COCONUTTOOLS_LOGGER_LEVEL_HPP_
#define COCONUTTOOLS_LOGGER_LEVEL_HPP_

#include "coconut-tools/utils/enum-definition.hpp"

namespace coconut_tools {
namespace logger {

/* enum class Level {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

std::istream& operator>>(std::istream& is, Level& level) {
	std::string levelString;
	is >> levelString;

	if (is) {
		levelString = std::toupper(levelString, is.getloc());

		if (levelString == "TRACE") {
			level = Level::TRACE;
		} else if (levelString == "DEBUG") {
			level = Level::DEBUG;
		} else if (levelString == "INFO") {
			level = Level::INFO;
		} else if (levelString == "WARNING") {
			level = Level::WARNING;
		} else if (levelString == "ERROR") {
			level = Level::ERROR;
		} else if (levelString == "CRITICAL") {
			level = Level::CRITICAL;
		} else {
			is.setstate(std::ios::failbit);
		}
	}

	return is;
} */

CT_ENUM_DEFINITION(Level, (TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL));

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_LEVEL_HPP_ */
