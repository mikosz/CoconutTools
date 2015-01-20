#ifndef COCONUT_TOOLS_SYSTEM_WINDOWS_CREATE_NEW_FILE_HPP_
#define COCONUT_TOOLS_SYSTEM_WINDOWS_CREATE_NEW_FILE_HPP_

#include <boost/filesystem/path.hpp>

namespace coconut_tools {
namespace system {
namespace windows {

bool createNewFile(const boost::filesystem::path& path);

} // namespace windows
} // namespace system
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_SYSTEM_WINDOWS_CREATE_NEW_FILE_HPP_ */
