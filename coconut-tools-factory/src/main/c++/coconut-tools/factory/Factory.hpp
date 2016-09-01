#ifndef COCONUT_TOOLS_FACTORY_FACTORY_HPP_
#define COCONUT_TOOLS_FACTORY_FACTORY_HPP_

#include <unordered_map>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace factory {

template <
    class IdentifierType,
    class InstanceType,
    template<class /* IdentifierType */, class /* InstanceType */> class StorageType,
    class CreatorType,
    class LockingPolicyType,
    template<class /* IdentifierType */> class ErrorPolicyType
    >
class Factory : public CreatorType {
public:

    using Identifier = IdentifierType;

    using IdentifierParam = typename boost::call_traits<Identifier>::param_type;

    using Instance = InstanceType;

    using LockingPolicy = LockingPolicyType;

    using Storage = StorageType<Identifier, Instance>;

    using StoredInstance = typename Storage::Permanent;

    using ErrorPolicy = ErrorPolicyType<Identifier>;

    StoredInstance create(const IdentifierParam id) {
        if (storage_.isStored(id)) {
            return storage_.get(id);
        } else {
			return doCreate(id);
        }
    }

    StoredInstance create(const IdentifierParam id) volatile {
    	return lockingPolicy_.lock(this)->create(id);
    }

private:

    LockingPolicy lockingPolicy_;

    Storage storage_;

};

} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_FACTORY_HPP_ */
