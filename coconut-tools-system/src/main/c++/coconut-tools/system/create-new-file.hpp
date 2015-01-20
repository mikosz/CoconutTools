#ifndef COCONUT_TOOLS_SYSTEM_CREATE_NEW_FILE_HPP_
#define COCONUT_TOOLS_SYSTEM_CREATE_NEW_FILE_HPP_

#include "platform.hpp"

namespace coconut_tools {
namespace system {

#if defined(PLATFORM_WINDOWS)
#	include "windows/create-new-file.hpp"
using windows::createNewFile;
#elif defined(PLATFORM_LINUX)
#	include "linux/create-new-file.hpp"
using linux::createNewFile;
#else
#	error "createNewFile not available for this platform"
#endif 

}  // namespace system
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_SYSTEM_CREATE_NEW_FILE_HPP_ */
