#ifndef COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_

#include <boost/filesystem/path.hpp>

#include "coconut-tools/concurrent/fake.hpp"

#include "coconut-tools/policy/creation/Functor.hpp"
#include "coconut-tools/factory.hpp"

#include "LogFile.hpp"

namespace coconut_tools {
namespace logger {
namespace log_file {

class LogFileFactory {
public:

	void registerLogFile(const std::string& id, const boost::filesystem::path& path, bool overwrite);

	LogFileSharedPtr create(const std::string& id);

private:

	using Factory = Factory<
		std::string,
		LogFile,
		factory::storage::Permanent,
		factory::CreatorRegistry<std::string, policy::creation::Functor<LogFileUniquePtr>, factory::error_policy::ExceptionThrowing>,
		concurrent::FakeMutex
		>;

	Factory factory_;

};

CT_SMART_POINTER_DEFINITONS(LogFileFactory);

} // namespace log_file
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_ */
