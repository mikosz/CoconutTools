#ifndef COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_
#define COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_

#include <functional>

namespace coconut_tools {
namespace utils {

class RaiiHelper {
public:

	typedef std::function<void()> Callback;

    RaiiHelper(Callback f) :
        f_(f) {
    }

    ~RaiiHelper() {
        if (f_) {
            f_();
        }
    }

    void reset() {
        f_ = Callback();
    }

private:

    Callback f_;

};

}  // namespace utils
}  // namespace CoconutTools

#endif /* COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_ */
