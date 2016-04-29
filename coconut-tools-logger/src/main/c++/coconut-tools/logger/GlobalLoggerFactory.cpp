#include "GlobalLoggerFactory.hpp"

#include <boost/filesystem.hpp>

#include "coconut-tools/configuration/parsers/XMLParser.hpp"
#include "coconut-tools/configuration/readers/HierarchicalConfigurationReader.hpp"

#include "coconut-tools/logger/log-file/GlobalLogFileFactory.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;

namespace /* anonymous */ {

logger::configuration::ConstLoggerConfigurationSharedPtr globalConfiguration(const boost::filesystem::path& path) {
	if (boost::filesystem::exists(path)) {
		auto configuration = coconut_tools::configuration::hierarchical::HierarchicalConfiguration::create();
		coconut_tools::configuration::parsers::XMLParser parser;
		coconut_tools::configuration::readers::HierarchicalConfigurationReader reader;
		reader.read(parser, path, configuration.get());
		return logger::configuration::LoggerConfigurationSharedPtr(
			new logger::configuration::LoggerConfiguration(configuration, log_file::GlobalLogFileFactory::instance())
			);
	} else {
		return logger::configuration::LoggerConfigurationSharedPtr();
	}
}

} // anonymous namespace

const boost::filesystem::path GlobalLoggerFactory::DEFAULT_CONFIGURATION_PATH("coconut-tools-logger.cfg.xml");

const boost::filesystem::path& GlobalLoggerFactory::defaultConfigurationPath() {
	return DEFAULT_CONFIGURATION_PATH;
}

GlobalLoggerFactory::GlobalLoggerFactory() :
	LoggerFactory(globalConfiguration(DEFAULT_CONFIGURATION_PATH))
{
}

void GlobalLoggerFactory::reloadConfiguration(const boost::filesystem::path& path) {
	reloadConfiguration(globalConfiguration(path));
}

void GlobalLoggerFactory::reloadConfiguration(const boost::filesystem::path& path) volatile {
	reloadConfiguration(globalConfiguration(path));
}
