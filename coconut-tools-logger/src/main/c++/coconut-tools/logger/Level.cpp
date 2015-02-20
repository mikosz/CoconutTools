#include "Level.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

std::istream& coconut_tools::logger::operator>>(std::istream& is, Level& level) {
	std::string levelString;
	is >> levelString;

	if (is) {
		boost::to_upper(levelString, is.getloc());

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
}
