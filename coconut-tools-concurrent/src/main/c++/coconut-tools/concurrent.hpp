#ifndef COCONUTTOOLS_CONCURRENT_HPP_
#define COCONUTTOOLS_CONCURRENT_HPP_

#include "concurrent/fake.hpp"
#include "concurrent/ILockable.hpp"
#include "concurrent/Lockable.hpp"
#include "concurrent/LockingPtr.hpp"
#include "concurrent/LockTraits.hpp"

namespace coconut_tools {

using concurrent::FakeLock;
using concurrent::FakeMutex;
using concurrent::ILockable;
using concurrent::Lockable;
using concurrent::LockingPtr;
using concurrent::LockTraits;

} // namespace coconut_tools

#endif /* COCONUTTOOLS_CONCURRENT_HPP_ */
