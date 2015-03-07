#include "Clock.hpp"

#include <iomanip>
#include <sstream>
#include <chrono>
#include <array>
#include <ctime>

#include <boost/algorithm/string/case_conv.hpp>

#include "coconut-tools/exceptions/LogicError.hpp"

#include "coconut-tools/utils/pointee.hpp"
#include "coconut-tools/utils/localtime-threadsafe.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::layout;

namespace /* anonymous */ {

const std::array<const std::string, static_cast<size_t>(Clock::Precision::SECONDS) + 1> CLOCK_PRECISION_NAMES = {
	"microseconds",
	"milliseconds",
	"seconds",
	};

const size_t FORMATTED_TIME_LENGTH = std::string("DD.MM.YYYY HH:MM:SS.UUUUUU").length();

} // anonymous namespace

void Clock::formatNow(std::ostream* osPtr) const {
	std::ostream& os = utils::pointee(osPtr);

	enum {
		MILLISECONDS_IN_MICROSECOND = 1000,
		MILLISECONDS_IN_SECOND = 1000,
		MICROSECONDS_IN_SECOND = 1000 * MILLISECONDS_IN_SECOND,
	};

	auto now = std::chrono::high_resolution_clock::now();
	auto tt = std::chrono::high_resolution_clock::to_time_t(now);
	std::tm tm;
	utils::localtime(&tm, tt);

	auto totalSeconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
	auto totalMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();

	std::string formattedTimeBuf;
	formattedTimeBuf.resize(FORMATTED_TIME_LENGTH + 1);
	size_t charsWritten =
		std::strftime(&formattedTimeBuf.front(), FORMATTED_TIME_LENGTH + 1, "%d.%m.%Y %H:%M:%S", &tm);
	if (charsWritten == 0) {
		throw exceptions::LogicError("Failed to format time - buffer too small?");
	}
	formattedTimeBuf.resize(charsWritten);
	os << formattedTimeBuf;

	auto microseconds = (totalMicroseconds - (totalSeconds * MICROSECONDS_IN_SECOND));

	switch (precision_) {
	case Clock::Precision::MILLISECONDS:
		os << '.' << std::setw(3) << (microseconds / MILLISECONDS_IN_MICROSECOND);
		break;
	case Clock::Precision::MICROSECONDS:
		os << '.' << microseconds;
		break;
	default:
		break;
	}
}

std::istream& coconut_tools::logger::layout::operator>>(std::istream& is, Clock::Precision& clockPrecision) {
	std::string clockPrecisionString;
	is >> clockPrecisionString;

	if (is) {
		boost::to_upper(clockPrecisionString, is.getloc());

		for (
			size_t clockPrecisionIndex = static_cast<size_t>(Clock::Precision::MICROSECONDS);
			clockPrecisionIndex < static_cast<size_t>(Clock::Precision::SECONDS) + 1;
			++clockPrecisionIndex
			) {
			if (CLOCK_PRECISION_NAMES[clockPrecisionIndex] == clockPrecisionString) {
				clockPrecision = static_cast<Clock::Precision>(clockPrecisionIndex);
				return is;
			}
		}

		is.setstate(std::ios::failbit);
	}

	return is;
}

std::ostream& coconut_tools::logger::layout::operator<<(std::ostream& os, Clock::Precision clockPrecision) {
	auto clockPrecisionIndex = static_cast<size_t>(clockPrecision);

	if (clockPrecisionIndex >= CLOCK_PRECISION_NAMES.size()) {
		throw exceptions::LogicError("Bad level index " + std::to_string(clockPrecisionIndex));
	}

	return os << CLOCK_PRECISION_NAMES[static_cast<size_t>(clockPrecisionIndex)];
}
