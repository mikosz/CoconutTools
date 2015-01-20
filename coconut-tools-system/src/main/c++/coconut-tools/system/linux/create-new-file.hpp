#ifndef COCONUT_TOOLS_SYSTEM_LINUX_CREATE_NEW_FILE_HPP_
#define COCONUT_TOOLS_SYSTEM_LINUX_CREATE_NEW_FILE_HPP_

#include <boost/filesystem/path.hpp>

namespace coconut_tools {
namespace system {
namespace linux {

bool createNewFile(const boost::filesystem::path& path);

} // namespace linux
} // namespace system
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_SYSTEM_LINUX_CREATE_NEW_FILE_HPP_ */
