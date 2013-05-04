#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_

#include <boost/shared_ptr.hpp>

#include "MappingStorage.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType, class LockingPolicy>
class PermanentStorage :
    public MappingStorage<
        IdentifierType,
        boost::shared_ptr<InstanceType>,
        boost::shared_ptr<InstanceType>,
        LockingPolicy
        >
{
public:

    PermanentStorage(LockingPolicy* lockingPolicyPtr) :
        MappingStorage<
                IdentifierType,
                boost::shared_ptr<InstanceType>,
                boost::shared_ptr<InstanceType>,
                LockingPolicy
                >(lockingPolicyPtr)
    {
    }

};

} // namespace storage
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_VOLATILESTORAGE_HPP_ */
