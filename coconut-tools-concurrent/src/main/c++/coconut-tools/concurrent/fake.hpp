#ifndef COCONUTTOOLS_CONCURRENT_FAKE_HPP_
#define COCONUTTOOLS_CONCURRENT_FAKE_HPP_

#include "LockTraits.hpp"

namespace coconut_tools {
namespace concurrent {

class FakeMutex {
};

class FakeLock {
public:

	FakeLock(FakeMutex& mutex) {
	}

};

template <>
class LockTraits<FakeMutex> {
public:

    using Mutex = FakeMutex;

    using UniqueLock = FakeLock;

    using SharedLock = FakeLock;

};

} // namespace concurrent
} // namespace CoconutTools

#endif /* COCONUTTOOLS_CONCURRENT_FAKE_HPP_ */
