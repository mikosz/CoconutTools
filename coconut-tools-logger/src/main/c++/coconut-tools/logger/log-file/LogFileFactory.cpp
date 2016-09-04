#include "LogFileFactory.hpp"

using namespace coconut_tools;
using namespace coconut_tools::logger;
using namespace coconut_tools::logger::log_file;

namespace /* anonymous */ {

LogFileUniquePtr create(const boost::filesystem::path& path, bool overwrite) {
	return LogFileUniquePtr(new LogFile(path, overwrite));
}

} // anonymous namespace

void LogFileFactory::registerLogFile(
	const std::string& id,
	const boost::filesystem::path& path,
	bool overwrite
	) {
	factory_.registerCreator(
		id,
		policy::creation::Functor<LogFileUniquePtr>([=]() { return ::create(path, overwrite); })
		);
}

LogFileSharedPtr LogFileFactory::create(const std::string& id) {
	return factory_.create(id);
}
