#include "tmp-file.hpp"

#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/function.hpp>

#include "create-new-file.hpp"
#include "SystemError.hpp"

using namespace coconut_tools;
using namespace coconut_tools::system;

namespace /* anonymous */ {

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
    return uniqueCreate(prefix, suffix, &createNewFile);
}

boost::filesystem::path coconut_tools::system::createTmpDir(const std::string& prefix,
        const std::string& suffix) {
    return uniqueCreate(prefix, suffix, &createDir);
}
