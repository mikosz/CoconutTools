#ifndef COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_
#define COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_

#include <functional>

namespace coconut_tools {
namespace utils {

class RaiiHelper {
public:

    RaiiHelper(std::function<void ()> f) :
        f_(f) {
    }

    ~RaiiHelper() {
        if (f_) {
            f_();
        }
    }

    void reset() {
        f_ = 0;
    }

private:

    std::function<void ()> f_;

};

}  // namespace utils
}  // namespace CoconutTools

#endif /* COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_ */
