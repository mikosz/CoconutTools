#include "LoggerConfiguration.hpp"

#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::configuration;

using coconut_tools::configuration::hierarchical::node::Path;
using coconut_tools::configuration::hierarchical::ConstHierarchicalConfigurationSharedPtr;

namespace /* anonymous */ {

ConstHierarchicalConfigurationSharedPtr getLoggerNode(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const std::string& loggerId
	) {
	return configuration->get((Path() / "loggers" / "logger")[Path("id").is(loggerId)]);
}

ConstHierarchicalConfigurationSharedPtr getRootNode(ConstHierarchicalConfigurationSharedPtr configuration) {
	return configuration->get(Path() / "root-logger");
}

ConstHierarchicalConfigurationSharedPtr getAppenderNode(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const std::string& appenderId
	) {
	return configuration->get((Path() / "appenders" / "appender")[Path("id").is(appenderId)]);
}

} // anonymous namespace

Level LoggerConfiguration::loggerLevel(const LoggerId& loggerId) const {
	std::vector<LoggerId> elements;
	boost::split(elements, loggerId, boost::is_any_of("."));

	while (!elements.empty()) {
		LoggerId nodeId = boost::join(elements, ".");

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

LoggerConfiguration::AppenderId LoggerConfiguration::appenderId(const LoggerId& loggerId) const {
	std::vector<LoggerId> elements;
	boost::split(elements, loggerId, boost::is_any_of("."));

	while (!elements.empty()) {
		LoggerId nodeId = boost::join(elements, ".");

		auto node = getLoggerNode(configuration_, nodeId);

		if (node) {
			auto appenderNode = node->get("appender");
			if (appenderNode) {
				return appenderNode->text();
			}
		}

		elements.pop_back();
	}

	auto rootNode = getRootNode(configuration_);
	if (rootNode) {
		auto appenderNode = rootNode->get("appender");
		if (appenderNode) {
			return appenderNode->text();
		}
	}

	throw LoggerConfigurationError("appender option not specified for logger \"" + loggerId + '"');
}

LoggerConfiguration::LayoutId LoggerConfiguration::layoutId(const AppenderId& appenderId) const {
	std::vector<LoggerId> elements;
	boost::split(elements, appenderId, boost::is_any_of("."));

	while (!elements.empty()) {
		AppenderId nodeId = boost::join(elements, ".");

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

LoggerConfiguration::AppenderTypeId LoggerConfiguration::appenderTypeId(const AppenderId& appenderId) const {
	std::vector<AppenderId> elements;
	boost::split(elements, appenderId, boost::is_any_of("."));

	while (!elements.empty()) {
		AppenderId nodeId = boost::join(elements, ".");

		auto node = getAppenderNode(configuration_, nodeId);

		if (node) {
			auto typeNode = node->get("type");
			if (typeNode) {
				return typeNode->text();
			}
		}

		elements.pop_back();
	}

	throw LoggerConfigurationError("type option not specified for appender \"" + appenderId + '"');
}
