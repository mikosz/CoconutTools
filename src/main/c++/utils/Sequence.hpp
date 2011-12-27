#ifndef COCONUT_TOOLS_UTILS_SEQUENCE_HPP_
#define COCONUT_TOOLS_UTILS_SEQUENCE_HPP_

#include <utility>

namespace coconut_tools {
namespace utils {

template <class T>
class Sequence {
public:

    Sequence(const std::pair<T, T> pair) :
        pair_(pair) {
    }

    const operator std::pair<T, T>&() const {
        return pair_;
    }

private:

    std::pair<T, T> pair_;

};

} // namespace utils
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_SEQUENCE_HPP_ */
