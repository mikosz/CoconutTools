#include "../platform.hpp"

#if defined(PLATFORM_LINUX)

#include "create-new-file.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../SystemError.hpp"

using namespace coconut_tools;
using namespace coconut_tools::system;
using namespace coconut_tools::system::linux;

bool coconut_tools::system::linux::createNewFile(const boost::filesystem::path& path) {
	if (open(path.string().c_str(), O_CREAT | O_EXCL, S_IRUSR | S_IWUSR) == -1) {
		if (errno == EEXIST) {
			return false;
		} else {
			throw SystemError("Failed to create file " + path.string());
		}
	} else {
		return true;
	}
}

#endif /* PLATFORM_LINUX */
