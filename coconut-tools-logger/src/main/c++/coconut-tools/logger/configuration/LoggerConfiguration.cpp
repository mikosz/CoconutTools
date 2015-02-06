#include "LoggerConfiguration.hpp"

#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::configuration;

using coconut_tools::configuration::hierarchical::node::Specifier;
using coconut_tools::configuration::hierarchical::HierarchicalConfigurationSharedPtr;

namespace /* anonymous */ {

HierarchicalConfigurationSharedPtr getLoggerNode(
	HierarchicalConfigurationSharedPtr configuration,
	const std::string& loggerId
	) {
	return configuration->get((Specifier() / "loggers" / "logger")[Specifier("id").is(loggerId)]);
}

HierarchicalConfigurationSharedPtr getRootNode(HierarchicalConfigurationSharedPtr configuration) {
	return configuration->get(Specifier() / "root-logger");
}

HierarchicalConfigurationSharedPtr getAppenderNode(
	HierarchicalConfigurationSharedPtr configuration,
	const std::string& appenderId
	) {
	return configuration->get((Specifier() / "appenders" / "appender")[Specifier("id").is(appenderId)]);
}

} // anonymous namespace

Level LoggerConfiguration::loggerLevel(const LoggerId& loggerId) const {
	std::vector<LoggerId> elements;
	boost::split(elements, loggerId, boost::is_any_of("."));

	while (!elements.empty()) {
		LoggerId nodeId;
		boost::join(elements, ".");

		auto node = getLoggerNode(configuration_, nodeId);

		if (node) {
			auto levelNode = node->get("level");
			if (levelNode) {
				return boost::lexical_cast<Level>(levelNode->text());
			}
		}

		elements.pop_back();
	}

	auto rootNode = getRootNode(configuration_);
	if (rootNode) {
		auto levelNode = rootNode->get("level");
		if (levelNode) {
			return boost::lexical_cast<Level>(levelNode->text());
		}
	}

	throw LoggerConfigurationError("level option not specified for logger \"" + loggerId + '"');
}

LoggerConfiguration::LayoutId LoggerConfiguration::layoutId(const AppenderId& appenderId) const {
	std::vector<LoggerId> elements;
	boost::split(elements, appenderId, boost::is_any_of("."));

	while (!elements.empty()) {
		LoggerId nodeId;
		boost::join(elements, ".");

		auto node = getAppenderNode(configuration_, nodeId);

		if (node) {
			auto layoutNode = node->get("layout");
			if (layoutNode) {
				return layoutNode->text();
			}
		}

		elements.pop_back();
	}

	throw LoggerConfigurationError("layout option not specified for appender \"" + appenderId + '"');
}
