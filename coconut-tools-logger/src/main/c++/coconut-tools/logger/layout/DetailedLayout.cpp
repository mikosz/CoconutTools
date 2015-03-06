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
	clock_.precision() = configurationNode->getAs<Clock::Precision>("time-precision");
}
