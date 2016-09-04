#ifndef COCONUTTOOLS_SINGLETON_SINGLETON_HPP_
#define COCONUTTOOLS_SINGLETON_SINGLETON_HPP_

#include <cstdlib>
#include <memory>

#include <boost/noncopyable.hpp>

#include "coconut-tools/concurrent/LockTraits.hpp"

#include "coconut-tools/policy/creation/New.hpp"

namespace coconut_tools {
namespace singleton {

template <
	class InstanceType,
	class MutexType,
	class CreatorType = policy::creation::New<InstanceType>
	>
class Singleton : boost::noncopyable {
public:

	using Instance = InstanceType;

	using InstancePtr = std::shared_ptr<InstanceType>;

    using Creator = CreatorType;

    static InstancePtr instance() {
        if (!instance_) {
			Lock lock(mutex());
            if (!instance_) {
				Creator creator;
                instance_.reset(creator.create().release());
                std::atexit(&Singleton::destroy);
            }
        }
        return instance_;
    }

    static void setInstance(std::unique_ptr<Instance>&& instance) {
		Lock lock(mutex());
    	if (!instance_) {
    		std::atexit(&Singleton::destroy);
    	}
    	instance_.reset(instance.release());
    }

private:

	using Lock = typename concurrent::LockTraits<MutexType>::UniqueLock;

    static InstancePtr instance_;

    static void destroy() {
        if (instance_) {
			Lock lock(mutex());
            if (instance_) {
                instance_.reset();
            }
        }
    }

	static MutexType& mutex() {
		static MutexType mutex_;
		return mutex_;
	}

};

template <class InstanceType, class LockingPolicy, class Creator>
typename Singleton<InstanceType, LockingPolicy, Creator>::InstancePtr Singleton<InstanceType, LockingPolicy, Creator>::instance_;

} // namespace singleton
} // namespace coconut_tools

#endif /* COCONUTTOOLS_SINGLETON_SINGLETON_HPP_ */
