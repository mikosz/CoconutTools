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

const ConstHierarchicalConfigurationSharedPtr EMPTY_NODE;

ConstHierarchicalConfigurationSharedPtr getNode(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& basePath,
	const std::string& id,
	const Path& childPath
	) {
	return configuration->getOptional(basePath[Path("id").is(id)] / childPath, EMPTY_NODE);
}

ConstHierarchicalConfigurationSharedPtr getDerivedNode(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& basePath,
	const std::string& id,
	const Path& childPath
	) {
	std::vector<std::string> elements;
	boost::split(elements, id, boost::is_any_of("."));

	while (!elements.empty()) {
		auto nodeId = boost::join(elements, ".");
		auto node = getNode(configuration, basePath, nodeId, childPath);

		if (node) {
			return node;
		}

		elements.pop_back();
	}

	return EMPTY_NODE;
}

ConstHierarchicalConfigurationSharedPtr getRootLoggerNode(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& childPath
	) {
	return configuration->getOptional("root-logger" / childPath, EMPTY_NODE);
}

ConstHierarchicalConfigurationSharedPtr getLoggerNode(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& basePath,
	const std::string& id,
	const Path& childPath
	) {
	auto node = getDerivedNode(configuration, basePath, id, childPath);
	if (!node) {
		node = getRootLoggerNode(configuration, childPath);
	}

	return node;
}

} // anonymous namespace

Level LoggerConfiguration::loggerLevel(const LoggerId& loggerId) const {
	auto node = getLoggerNode(configuration_, "loggers/logger", loggerId, "level");
	if (!node) {
		throw LoggerConfigurationError("level option not specified for logger \"" + loggerId + '"');
	}

	return boost::lexical_cast<Level>(node->text());
}

LoggerConfiguration::AppenderId LoggerConfiguration::appenderId(const LoggerId& loggerId) const {
	auto node = getLoggerNode(configuration_, "loggers/logger", loggerId, "appender-id");
	if (!node) {
		throw LoggerConfigurationError("appender option not specified for logger \"" + loggerId + '"');
	}

	return node->text();
}

LoggerConfiguration::LayoutId LoggerConfiguration::layoutId(const AppenderId& appenderId) const {
	auto node = getDerivedNode(configuration_, "appenders/appender", appenderId, "layout-id");
	if (!node) {
		throw LoggerConfigurationError("layout option not specified for appender \"" + appenderId + '"');
	}

	return node->text();
}

LoggerConfiguration::AppenderTypeId LoggerConfiguration::appenderTypeId(const AppenderId& appenderId) const {
	auto node = getDerivedNode(configuration_, "appenders/appender", appenderId, "type");
	if (!node) {
		throw LoggerConfigurationError("type option not specified for appender \"" + appenderId + '"');
	}

	return node->text();
}
