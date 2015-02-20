#include "Level.hpp"

#include <array>

#include "coconut-tools/exceptions/LogicError.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace /* anonymous */ {

std::array<const std::string, static_cast<size_t>(Level::CRITICAL) + 1> LEVEL_NAMES = {
	"TRACE",
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR",
	"CRITICAL",
	};

} // anonymous namespace

std::istream& coconut_tools::logger::operator>>(std::istream& is, Level& level) {
	std::string levelString;
	is >> levelString;

	if (is) {
		boost::to_upper(levelString, is.getloc());

		for (
			size_t levelIndex = static_cast<size_t>(Level::TRACE);
			levelIndex < static_cast<size_t>(Level::CRITICAL) + 1;
			++levelIndex
			) {
			if (LEVEL_NAMES[levelIndex] == levelString) {
				level = static_cast<Level>(levelIndex);
				return is;
			}
		}

		is.setstate(std::ios::failbit);
	}

	return is;
}

std::ostream& coconut_tools::logger::operator<<(std::ostream& os, Level level) {
	auto levelIndex = static_cast<size_t>(level);

	if (levelIndex >= LEVEL_NAMES.size()) {
		throw exceptions::LogicError("Bad level index " + std::to_string(levelIndex));
	}

	return os << LEVEL_NAMES[static_cast<size_t>(level)];
}
