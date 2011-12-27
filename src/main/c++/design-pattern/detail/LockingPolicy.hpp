#ifndef COCONUTTOOLS_DESIGN_PATTERN_DETAIL_LOCKINGPOLICY_HPP_
#define COCONUTTOOLS_DESIGN_PATTERN_DETAIL_LOCKINGPOLICY_HPP_

#include <boost/thread/mutex.hpp>

#include "utils/Null.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace detail {

class EmptyLockingPolicy {
public:

    typedef utils::Null Mutex;

    typedef utils::Null Lock;

};

class BoostLockingPolicy {
public:

    typedef boost::mutex Mutex;

    typedef boost::mutex::scoped_lock Lock;

};

} // namespace detail
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUTTOOLS_DESIGN_PATTERN_DETAIL_LOCKINGPOLICY_HPP_ */
