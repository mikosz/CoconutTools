#ifndef COCONUTTOOLS_CONCURRENT_HPP_
#define COCONUTTOOLS_CONCURRENT_HPP_

#include "concurrent/fake.hpp"
#include "concurrent/Lockable.hpp"
#include "concurrent/LockingPtr.hpp"
#include "concurrent/LockTraits.hpp"
#include "concurrent/LockableInstance.hpp"

namespace coconut_tools {

using concurrent::FakeLock;
using concurrent::FakeMutex;
using concurrent::Lockable;
using concurrent::LockingPtr;
using concurrent::LockTraits;
using concurrent::LockableInstance;

} // namespace coconut_tools

#endif /* COCONUTTOOLS_CONCURRENT_HPP_ */
