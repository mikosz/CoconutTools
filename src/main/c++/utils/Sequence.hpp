#ifndef COCONUT_TOOLS_UTILS_SEQUENCE_HPP_
#define COCONUT_TOOLS_UTILS_SEQUENCE_HPP_

#include <boost/call_traits.hpp>

#include <utility>

namespace coconut_tools {
namespace utils {

template <class T>
class Sequence {
public:

    Sequence(const typename boost::call_traits<T>::param_type first,
            const typename boost::call_traits<T>::param_type second) :
            pair_(first, second) {
    }

    Sequence(const std::pair<T, T> pair) :
        pair_(pair) {
    }

    operator const std::pair<T, T>&() const {
        return pair_;
    }

    bool atEnd() const {
        return pair_.first == pair_.second;
    }

    void next() {
        ++pair_.first;
    }

    T& current() {
        return pair_.first;
    }

private:

    std::pair<T, T> pair_;

};

} // namespace utils
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_SEQUENCE_HPP_ */
