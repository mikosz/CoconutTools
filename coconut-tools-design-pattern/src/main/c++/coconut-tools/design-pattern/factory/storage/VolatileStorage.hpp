#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_

#include <boost/weak_ptr.hpp>

#include "MappingStorage.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType, class LockingPolicy>
class VolatileStorage :
    public MappingStorage<
        IdentifierType,
        boost::weak_ptr<InstanceType>,
        boost::shared_ptr<InstanceType>,
        LockingPolicy
        >
{
private:

    typedef MappingStorage<
                IdentifierType,
                boost::weak_ptr<InstanceType>,
                boost::shared_ptr<InstanceType>,
                LockingPolicy
                >
            Super;

public:

    typedef typename Super::Instance Instance;

    typedef typename Super::Identifier Identifier;

    typedef typename Super::IdentifierParam IdentifierParam;

    typedef typename Super::Permanent Permanent;

    typedef typename Super::Stored Stored;

    VolatileStorage(LockingPolicy* lockingPolicyPtr) :
        Super(lockingPolicyPtr) {
    }

    Permanent get(const IdentifierParam identifier) const {
        Stored stored = Super::getStored(identifier);
        return stored.lock();
    }

    Permanent get(const IdentifierParam identifier) const volatile {
        return this->lockingPolicy().lock(this)->get(identifier);
    }

};

} // namespace storage
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_ */
