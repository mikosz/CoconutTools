#include "../platform.hpp"

#if defined(PLATFORM_WINDOWS)

#include "create-new-file.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "../SystemError.hpp"

using namespace coconut_tools;
using namespace coconut_tools::system;
using namespace coconut_tools::system::windows;

bool coconut_tools::system::linux::createNewFile(const boost::filesystem::path& path) {
	HANDLE h = CreateFile(path.string().c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, 0);
	if (SUCCEEDED(h)) {
		return true;
	} else if (GetLastError() == ERROR_ALREADY_EXISTS) {
		return false;
	} else {
		throw SystemError("Failed to create file " + path.string());
	}
}

#endif /* PLATFORM_WINDOWS */
