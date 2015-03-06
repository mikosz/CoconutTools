#ifndef COCONUTTOOLS_LOGGER_LAYOUT_DETAILEDLAYOUT_HPP_
#define COCONUTTOOLS_LOGGER_LAYOUT_DETAILEDLAYOUT_HPP_

#include "coconut-tools/exceptions/LogicError.hpp"

#include "../configuration/LoggerConfiguration.hpp"
#include "Layout.hpp"
#include "Clock.hpp"

namespace coconut_tools {
namespace logger {
namespace layout {

class DetailedLayout : public Layout {
public:

	static const std::string CLASS_NAME;

	DetailedLayout(Clock::Precision clockPrecision) :
		clock_(clockPrecision)
	{
		if (clockPrecision == Clock::Precision::UNKNOWN) {
			throw exceptions::LogicError("Invalid clock precision");
		}
	}

	/**
	 * Formats the logged string, e.g.:
	 *   "21.02.2015-08:31:12.125631 @ DetailedLayout.hpp:75 [WARNING] - logger-category"
	 *   "some warning message"
	 */
	std::string format(Level level, const Context& context, const std::string& message) override;

protected:

	void doInitialise(const Id& layoutId, const logger::configuration::LoggerConfiguration& configuration) override;

private:

	friend class utils::Initialiser<
		Layout,
		const Id&,
		const logger::configuration::LoggerConfiguration&
	>;

	DetailedLayout() {
	}

	Clock clock_;

};

} // namespace layout
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LAYOUT_DETAILEDLAYOUT_HPP_ */
