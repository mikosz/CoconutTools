#ifndef COCONUT_TOOLS_TEST_TEST_UTILS_HPP_
#define COCONUT_TOOLS_TEST_TEST_UTILS_HPP_

#include <string>
#include <fstream>

#include <boost/filesystem.hpp>

#include "coconut-tools/system/tmp-file.hpp"

namespace coconut_tools {
namespace test_utils {

inline void writeToFile(const boost::filesystem::path& path, const std::string& s) {
    std::ofstream ofs(path.string().c_str());
    ofs << s;
    ofs.close();
}

class ResourcesDirFixture {
public:

    ResourcesDirFixture() :
        resourcesDir_(system::createTmpDir(".test-resources-")) {
    }

    ~ResourcesDirFixture() {
        boost::filesystem::remove_all(resourcesDir_);
    }

    const boost::filesystem::path& resourcesDir() const {
        return resourcesDir_;
    }

private:

    boost::filesystem::path resourcesDir_;

};

}  // namespace test_utils
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_TEST_TEST_UTILS_HPP_ */
