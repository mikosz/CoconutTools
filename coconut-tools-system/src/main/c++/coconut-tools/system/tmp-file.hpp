#ifndef COCONUT_TOOLS_SYSTEM_TMP_FILE_HPP_
#define COCONUT_TOOLS_SYSTEM_TMP_FILE_HPP_

#include <string>

#include <boost/filesystem/path.hpp>

namespace coconut_tools {
namespace system {

boost::filesystem::path createTmpFile(const std::string& prefix = "", const std::string& suffix = "");

boost::filesystem::path createTmpDir(const std::string& prefix = "", const std::string& suffix = "");

}  // namespace system
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_SYSTEM_TMP_FILE_HPP_ */
