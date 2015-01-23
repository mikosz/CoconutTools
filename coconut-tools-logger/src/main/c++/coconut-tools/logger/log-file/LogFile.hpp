#ifndef COCONUTTOOLS_LOGGER_LOGFILE_LOGFILE_HPP_
#define COCONUTTOOLS_LOGGER_LOGFILE_LOGFILE_HPP_

#include <fstream>

#include <boost/filesystem/path.hpp>

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

namespace coconut_tools {
namespace logger {
namespace log_file {

class LogFile {
public:

	explicit LogFile(const boost::filesystem::path& path, bool overwrite) :
		stream_(
				path.string().c_str(),
				overwrite ? std::ios::out : std::ios::app
				) {
	}

	virtual ~LogFile() {
	}

	virtual void write(const std::string& message) {
		stream_ << message;
		stream_.flush();
	}

private:

	std::ofstream stream_;

};

CT_SMART_POINTER_DEFINITONS(LogFile);

} // namespace log_file
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_LOGFILE_LOGFILE_HPP_ */
