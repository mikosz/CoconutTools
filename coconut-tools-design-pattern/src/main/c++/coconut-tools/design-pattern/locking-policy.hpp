#ifndef COCONUTTOOLS_DESIGN_PATTERN_LOCKING_POLICY_HPP_
#define COCONUTTOOLS_DESIGN_PATTERN_LOCKING_POLICY_HPP_

#include <boost/thread/mutex.hpp>

#include "coconut-tools/utils/Null.hpp"

namespace coconut_tools {
namespace design_pattern {

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

} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUTTOOLS_DESIGN_PATTERN_LOCKING_POLICY_HPP_ */
