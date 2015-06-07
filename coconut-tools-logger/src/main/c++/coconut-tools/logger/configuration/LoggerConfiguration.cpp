#include "LoggerConfiguration.hpp"

#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::configuration;

using coconut_tools::configuration::hierarchical::node::Path;
using coconut_tools::configuration::hierarchical::ConstHierarchicalConfigurationSharedPtr;
using coconut_tools::configuration::hierarchical::HierarchicalConfiguration;

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

HierarchicalConfiguration::Nodes getNodes(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& basePath,
	const std::string& id,
	const Path& childPath
	) {
	HierarchicalConfiguration::Nodes nodes;
	configuration->getAll(basePath[Path("id").is(id)] / childPath, &nodes);
	return nodes;
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

HierarchicalConfiguration::Nodes getDerivedNodes(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& basePath,
	const std::string& id,
	const Path& childPath,
	const Path& aggregateWithParentPath
	) {
	std::vector<std::string> elements;
	boost::split(elements, id, boost::is_any_of("."));

	HierarchicalConfiguration::Nodes result;

	while (!elements.empty()) {
		auto nodeId = boost::join(elements, ".");
		auto nodes = getNodes(configuration, basePath, nodeId, childPath);

		if (!nodes.empty()) {
			std::copy(nodes.begin(), nodes.end(), std::back_inserter(result));
			
			auto aggregateWithParentPathNode = getNode(configuration, basePath, nodeId, aggregateWithParentPath);
			if (aggregateWithParentPathNode && !boost::lexical_cast<bool>(aggregateWithParentPathNode->text())) {
				break;
			}
		}

		elements.pop_back();
	}

	return result;
}

ConstHierarchicalConfigurationSharedPtr getRootLoggerNode(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& childPath
	) {
	return configuration->getOptional("root-logger" / childPath, EMPTY_NODE);
}

HierarchicalConfiguration::Nodes getRootLoggerNodes(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& childPath
	) {
	HierarchicalConfiguration::Nodes result;
	configuration->getAll("root-logger" / childPath, &result);
	return result;
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

HierarchicalConfiguration::Nodes getLoggerNodes(
	ConstHierarchicalConfigurationSharedPtr configuration,
	const Path& basePath,
	const std::string& id,
	const Path& childPath,
	const Path& aggregateWithParentPath
	) {
	auto nodes = getDerivedNodes(configuration, basePath, id, childPath, aggregateWithParentPath);
	
	if (nodes.empty()) {
		nodes = getRootLoggerNodes(configuration, childPath);
	}

	return nodes;
}

} // anonymous namespace

Level LoggerConfiguration::loggerLevel(const LoggerId& loggerId) const {
	auto node = getLoggerNode(configuration_, "loggers/logger", loggerId, "level");
	if (!node) {
		throw LoggerConfigurationError("level option not specified for logger \"" + loggerId + '"');
	}

	return boost::lexical_cast<Level>(node->text());
}

Level LoggerConfiguration::appenderLevel(const AppenderId& appenderId) const {
	auto node = getDerivedNode(configuration_, "appenders/appender", appenderId, "level");
	if (!node) {
		return Level::TRACE;
	}

	return boost::lexical_cast<Level>(node->text());
}

LoggerConfiguration::AppenderIds LoggerConfiguration::appenderIds(const LoggerId& loggerId) const {
	auto nodes =
		getLoggerNodes(configuration_, "loggers/logger", loggerId, "appenders/appender", "aggregate-with-parent");

	AppenderIds result;

	for (auto node : nodes) {
		result.push_back(node->text());
	}

	return result;
}

LoggerConfiguration::LayoutId LoggerConfiguration::layoutId(const AppenderId& appenderId) const {
	auto node = getDerivedNode(configuration_, "appenders/appender", appenderId, "layout");
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

LoggerConfiguration::LayoutId LoggerConfiguration::layoutTypeId(const LayoutId& layoutId) const {
	auto node = getDerivedNode(configuration_, "layouts/layout", layoutId, "type");
	if (!node) {
		throw LoggerConfigurationError("type option not specified for layout \"" + layoutId + '"');
	}

	return node->text();
}

LoggerConfiguration::Configuration LoggerConfiguration::layoutConfiguration(const LayoutId& layoutId) const {
	auto node = getDerivedNode(configuration_, "layouts/layout", layoutId, "configuration");
	if (!node) {
		throw LoggerConfigurationError("configuration option not specified for layout \"" + layoutId + '"');
	}

	return node;
}
