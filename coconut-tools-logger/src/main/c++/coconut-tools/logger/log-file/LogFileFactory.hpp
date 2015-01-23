#ifndef COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_
#define COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_

#include <boost/filesystem/path.hpp>

#include "coconut-tools/design-pattern/factory.hpp"

#include "LogFile.hpp"

namespace coconut_tools {
namespace logger {
namespace log_file {

class LogFileFactory {
public:

	void registerLogFile(const std::string& id, const boost::filesystem::path& path, bool overwrite);

private:

	typedef design_pattern::Factory<
		std::string,
		LogFileSharedPtr,
		design_pattern::PermanentStorage,
		design_pattern::FunctorCreator,
		design_pattern::NoLockingPolicy,
		design_pattern::ExceptionThrowingErrorPolicy
		> Factory;

	Factory factory_;

};

CT_SMART_POINTER_DEFINITONS(LogFileFactory);

} // namespace log_file
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGFILE_LOGFILEFACTORY_HPP_ */
