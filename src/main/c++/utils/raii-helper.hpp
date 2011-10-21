#ifndef COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_
#define COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_

#include <boost/function.hpp>

namespace CoconutTools {
namespace utils {

class RaiiHelper {
public:

    RaiiHelper(boost::function<void ()> f) :
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

    boost::function<void ()> f_;

};

}  // namespace utils
}  // namespace CoconutTools

#endif /* COCONUT_TOOLS_UTILS_RAII_HELPER_HPP_ */
