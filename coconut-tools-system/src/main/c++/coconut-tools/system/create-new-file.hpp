#ifndef COCONUT_TOOLS_SYSTEM_CREATE_NEW_FILE_HPP_
#define COCONUT_TOOLS_SYSTEM_CREATE_NEW_FILE_HPP_

#include "platform.hpp"

#if defined(CT_PLATFORM_WINDOWS)
#	include "windows/create-new-file.hpp"
using coconut_tools::system::windows::createNewFile;
#elif defined(CT_PLATFORM_LINUX)
#	include "linux/create-new-file.hpp"
using coconut_tools::system::linux::createNewFile;
#else
#	error "createNewFile not available for this platform"
#endif 

#endif /* COCONUT_TOOLS_SYSTEM_CREATE_NEW_FILE_HPP_ */
