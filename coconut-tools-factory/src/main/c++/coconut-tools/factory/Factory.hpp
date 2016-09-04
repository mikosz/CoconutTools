#ifndef COCONUT_TOOLS_FACTORY_FACTORY_HPP_
#define COCONUT_TOOLS_FACTORY_FACTORY_HPP_

#include <unordered_map>

#include <boost/call_traits.hpp>

#include "coconut-tools/concurrent/Lockable.hpp"

namespace coconut_tools {
namespace factory {

template <
    class IdentifierType,
    class InstanceType,
    template<class /* IdentifierType */, class /* InstanceType */> class StorageType,
    class CreatorType,
    class MutexType
    >
class Factory :
	public CreatorType,
	public concurrent::Lockable<
		Factory<IdentifierType, InstanceType, StorageType, CreatorType, MutexType>,
		MutexType
		>
{
public:

    using Identifier = IdentifierType;

    using IdentifierParam = typename boost::call_traits<Identifier>::param_type;

    using Instance = InstanceType;

    using Storage = StorageType<Identifier, Instance>;

    using StoredInstance = typename Storage::Instance;

    StoredInstance create(const IdentifierParam id) {
		if (!storage_.isStored(id)) {
			storage_.store(id, doCreate(id));
		}
		return storage_.get(id);
    }

    StoredInstance create(const IdentifierParam id) volatile {
    	return lock()->create(id);
    }

private:

    Storage storage_;

};

} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_FACTORY_HPP_ */
