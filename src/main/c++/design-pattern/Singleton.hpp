#ifndef COCONUTTOOLS_DESIGN_PATTERN_SINGLETON_HPP_
#define COCONUTTOOLS_DESIGN_PATTERN_SINGLETON_HPP_

#include <cstdlib>

#include <boost/noncopyable.hpp>

namespace coconut_tools {
namespace design_pattern {

template <class T, class LockingPolicy>
class Singleton : boost::noncopyable {
public:

    static T& instance() {
        if (!instance_) {
            typename LockingPolicy::Lock lock(*mutex_);
            if (!instance_) {
                instance_ = new T;
                std::atexit(&Singleton::destroy);
            }
        }
        return *instance_;
    }

private:

    static typename LockingPolicy::Mutex* mutex_;

    static T* volatile instance_;

    static void destroy() {
        if (instance_) {
            typename LockingPolicy::Lock lock(*mutex_);
            if (instance_) {
                delete instance_;
                instance_ = 0;
            }
        }
    }

};

// Yes, it's a memory leak. Without it, the code cannot be thread safe (imo).
template <class T, class LockingPolicy>
typename LockingPolicy::Mutex* Singleton::mutex_ = new typename LockingPolicy::Mutex;

template <class T, class LockingPolicy>
T* Singleton::instance_ = 0;

} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUTTOOLS_DESIGN_PATTERN_SINGLETON_HPP_ */
