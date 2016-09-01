#ifndef COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_

#include <boost/filesystem/path.hpp>

#include "coconut-tools/policy/locking/None.hpp"
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

	using Factory = factor::Factory<
		std::string,
		LogFileSharedPtr,
		design_pattern::Permanent,
		design_pattern::FunctorCreator<LogFileUniquePtr>,
		policy::locking::None,
		factory::error_policy::ExceptionThrowingErrorPolicy
		>;

	Factory factory_;

};

CT_SMART_POINTER_DEFINITONS(LogFileFactory);

} // namespace log_file
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_ */
