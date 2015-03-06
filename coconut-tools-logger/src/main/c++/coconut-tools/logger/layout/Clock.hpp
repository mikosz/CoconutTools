#ifndef COCONUTTOOLS_LOGGER_LAYOUT_CLOCK_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_CLOCK_HPP_

#include <iosfwd>

namespace coconut_tools {
namespace logger {
namespace layout {

class Clock {
public:

	enum class Precision {
		UNKNOWN = -1,
		MICROSECONDS,
		MILLISECONDS,
		SECONDS
	};

	Clock() :
		precision_(Precision::UNKNOWN)
	{
	}

	Clock(Precision precision) :
		precision_(precision)
	{
	}

	void formatNow(std::ostream* osPtr) const;

	Precision& precision() {
		return precision_;
	}

private:

	Precision precision_;

};

std::istream& operator>>(std::istream& is, Clock::Precision& clockPrecision);

std::ostream& operator<<(std::ostream& os, Clock::Precision clockPrecision);

} // namespace layout
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_CLOCK_HPP_ */
