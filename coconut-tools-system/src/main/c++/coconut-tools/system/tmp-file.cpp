#include "tmp-file.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/function.hpp>

#include "SystemError.hpp"

using namespace coconut_tools::system;

namespace {

bool createDir(const boost::filesystem::path& path) {
    try {
        return boost::filesystem::create_directories(path);
    } catch (const boost::filesystem::filesystem_error&) {
        if (boost::filesystem::exists(path) && !boost::filesystem::is_directory(path)) {
            return false;
        } else {
            throw;
        }
    }
}

#warning createFile is non-portable
bool createFile(const boost::filesystem::path& path) {
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

boost::filesystem::path uniqueCreate(const std::string& prefix, const std::string& suffix,
        boost::function<bool(const boost::filesystem::path&)> creator) {
    size_t idx = 0;
    while (true) {
        std::ostringstream oss;
        oss << prefix << idx++ << suffix;
        if (creator(oss.str())) {
            return oss.str();
        }
        oss.str("");
    }
}

} // anonymous namespace

boost::filesystem::path coconut_tools::system::createTmpFile(const std::string& prefix,
        const std::string& suffix) {
    return uniqueCreate(prefix, suffix, &createFile);
}

boost::filesystem::path coconut_tools::system::createTmpDir(const std::string& prefix,
        const std::string& suffix) {
    return uniqueCreate(prefix, suffix, &createDir);
}
