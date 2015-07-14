#include "DetailedLayout.hpp"

#include <sstream>

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::layout;

const std::string DetailedLayout::CLASS_NAME("coconut_tools::logger::layout::DetailedLayout");

std::string DetailedLayout::format(Level level, const Context& context, const std::string& message) {
	std::ostringstream oss;
	clock_.formatNow(&oss);
	oss << " @ " << context.file << ':' << context.line << " [" << level << "] - "
		<< context.category << '\n' << message << "\n\n";

	return oss.str();
}

void DetailedLayout::doInitialise(
	const Id& layoutId,
	const logger::configuration::LoggerConfiguration& configuration
	) {
	auto configurationNode = configuration.layoutConfiguration(layoutId);
	try {
		clock_.precision() = configurationNode->getAs<Clock::Precision>("time-precision");
	} catch (const coconut_tools::configuration::BadValueType&) {
		throw logger::configuration::LoggerConfigurationError(
			"Bad time-precision value for layout " + layoutId + ": \"" + configurationNode->get("time-precision")->text() + "\".");
	} catch (const coconut_tools::configuration::MissingRequiredValue&) {
		throw logger::configuration::LoggerConfigurationError("Missing required configuration value \"time-precision\" for layout " + layoutId);
	}
}
