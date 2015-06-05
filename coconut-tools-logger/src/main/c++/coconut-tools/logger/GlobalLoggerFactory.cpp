#include "GlobalLoggerFactory.hpp"

#include <boost/filesystem.hpp>

#include "coconut-tools/configuration/parsers/XMLParser.hpp"
#include "coconut-tools/configuration/readers/HierarchicalConfigurationReader.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace /* anonymous */ {

const boost::filesystem::path DEFAULT_CONFIGURATION_PATH("coconut-tools-logger.cfg.xml");

logger::configuration::ConstLoggerConfigurationSharedPtr globalConfiguration() {
	if (boost::filesystem::exists(DEFAULT_CONFIGURATION_PATH)) {
		auto configuration = coconut_tools::configuration::hierarchical::HierarchicalConfiguration::create();
		coconut_tools::configuration::parsers::XMLParser parser;
		coconut_tools::configuration::readers::HierarchicalConfigurationReader reader;
		reader.read(parser, DEFAULT_CONFIGURATION_PATH, configuration.get());
		return logger::configuration::LoggerConfigurationSharedPtr(new logger::configuration::LoggerConfiguration(configuration));
	} else {
		return logger::configuration::LoggerConfigurationSharedPtr();
	}
}

} // anonymous namespace

GlobalLoggerFactory::GlobalLoggerFactory() :
	LoggerFactory(globalConfiguration())
{
}

void GlobalLoggerFactory::reloadConfiguration() {
	reloadConfiguration(globalConfiguration());
}

void GlobalLoggerFactory::reloadConfiguration() volatile {
	reloadConfiguration(globalConfiguration());
}
