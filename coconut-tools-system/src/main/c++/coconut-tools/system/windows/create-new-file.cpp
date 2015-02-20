#include "../platform.hpp"

#if defined(CT_PLATFORM_WINDOWS)

#include "create-new-file.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <boost/filesystem.hpp>

#include "../SystemError.hpp"

using namespace coconut_tools;
using namespace coconut_tools::system;
using namespace coconut_tools::system::windows;

bool coconut_tools::system::windows::createNewFile(const boost::filesystem::path& path) {
	HANDLE h = CreateFile(path.string().c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW, 0, 0);
	if (SUCCEEDED(h)) {
		CloseHandle(h);
		return true;
	} else {
		if (GetLastError() == ERROR_FILE_EXISTS) {
			return false;
		} else {
			throw SystemError("Failed to create file " + path.string(),
				std::error_code(GetLastError(), std::system_category()));
		}
	}
}

#endif /* CT_PLATFORM_WINDOWS */
