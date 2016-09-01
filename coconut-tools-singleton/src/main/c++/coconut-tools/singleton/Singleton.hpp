#ifndef COCONUTTOOLS_SINGLETON_SINGLETON_HPP_
#define COCONUTTOOLS_SINGLETON_SINGLETON_HPP_

#include <cstdlib>
#include <memory>

#include <boost/noncopyable.hpp>

#include "coconut-tools/policy/creation/New.hpp"

namespace coconut_tools {
namespace singleton {

template <
	class InstanceType,
	class LockingPolicyType,
	class CreatorType = policy::creation::New<InstanceType>
	>
class Singleton : boost::noncopyable {
public:

	typedef InstanceType Instance;

	typedef std::shared_ptr<InstanceType> InstancePtr;

    typedef CreatorType Creator;

    typedef LockingPolicyType LockingPolicy;

    static InstancePtr instance() {
        if (!instance_) {
            auto lock = lockingPolicy().lock(&instance_);
            if (!instance_) {
				Creator creator;
                instance_.reset(creator.create().release());
                std::atexit(&Singleton::destroy);
            }
        }
        return instance_;
    }

    static void setInstance(std::unique_ptr<Instance>&& instance) {
		auto lock = lockingPolicy().lock(&instance_);
    	if (!instance_) {
    		std::atexit(&Singleton::destroy);
    	}
    	instance_.reset(instance.release());
    }

private:

    static InstancePtr instance_;

    static void destroy() {
        if (instance_) {
			auto lock = lockingPolicy().lock(&instance_);
            if (instance_) {
                instance_.reset();
            }
        }
    }

	static LockingPolicy& lockingPolicy() {
		static std::unique_ptr<LockingPolicy> lockingPolicy_(new LockingPolicy);
		return *lockingPolicy_;
	}

};

template <class InstanceType, class LockingPolicy, class Creator>
typename Singleton<InstanceType, LockingPolicy, Creator>::InstancePtr Singleton<InstanceType, LockingPolicy, Creator>::instance_;

} // namespace singleton
} // namespace coconut_tools

#endif /* COCONUTTOOLS_SINGLETON_SINGLETON_HPP_ */
