#include "LogFileFactory.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::log_file;

namespace /* anonymous */ {

LogFileSharedPtr create(const boost::filesystem::path& path, bool overwrite) {
	return LogFileSharedPtr(new LogFile(path, overwrite));
}

} // anonymous namespace

void LogFileFactory::registerLogFile(
	const std::string& id,
	const boost::filesystem::path& path,
	bool overwrite
	) {
	factory_.registerCreator(id, std::bind(&create, path, overwrite));
}
