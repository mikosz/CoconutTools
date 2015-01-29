#include "LoggerConfiguration.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::configuration;

using coconut_tools::configuration::hierarchical::NodeSpecifier;
using coconut_tools::configuration::HierarchicalConfigurationSharedPtr;

namespace /* anonymous */ {

HierarchicalConfigurationSharedPtr getLoggerNode(
	HierarchicalConfigurationSharedPtr configuration,
	const std::string& loggerId
	) {
	return configuration->get((NodeSpecifier() / "loggers" / "logger")[NodeSpecifier("id").is(loggerId)]);
}

} // anonymous namespace

Level LoggerConfiguration::loggerLevel(const LoggerId& loggerId) const {
	HierarchicalConfigurationSharedPtr configuration;
	
	while (true) {
		configuration = getLoggerNode(configuration_, loggerId);

		if (configuration) {
			HierarchicalConfigurationSharedPtr levelNode = configuration->get("level");
			if (levelNode) {
				return Level()
			}
		}
	}
}
