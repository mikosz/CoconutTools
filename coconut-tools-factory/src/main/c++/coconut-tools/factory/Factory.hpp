#ifndef COCONUT_TOOLS_FACTORY_FACTORY_HPP_
#define COCONUT_TOOLS_FACTORY_FACTORY_HPP_

#include <unordered_map>

#include <boost/call_traits.hpp>

#include "coconut-tools/concurrent/Lockable.hpp"

namespace coconut_tools {
namespace factory {

/**
 * A generic implementation of the "Factory" design pattern.
 * 
 * @param IdentifierType Type of the parameter identifying objects to be created
 * @param InstanceType Type, or supertype, of objects that will be returned by the create function. This
 *     type will be wrapped into some storage type.
 * @param StorageType A policy class that stores created objects. Requirements for this class are:
 *     * default-constructible
 *     * defines an Instance type - this is the final type that will be returned by the create() function
 *     * implements a isStored(IdentifierType) function, returning true iff it is capable of returning an
 *       object with the provided identifier
 *     * implements a store(IdentifierType, decltype(CreatorType::doCreate(...))) function that stores the
 *       provided object and returns it as a StorageType::Instance
 *     * implements a get(IdentifierType) that returns a stored StorageType::Instance
 * @param CreatorType A policy class from which Factory publicly inherits. It may provide additional functions
 *     to be exposed for the user. Required to implement a doCreate(IdentifierType, ...) function, that returns
 *     a newly created object. The type must be compatible with StorageType's store function parameter.
 * @param MutexType Type of a the mutex that will be used to achieve thread safety. Must be compatible with
 *     concurrent::Lockable's MutexType parameter.
 */
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

	template <class... CreatorParams>
	Factory(CreatorParams&&... creatorParams) :
		CreatorType(std::forward<CreatorParams>(creatorParams)...)
	{
	}

	template <class... CreatorParams>
    StoredInstance create(const IdentifierParam id, CreatorParams&&... creatorParams) {
		if (!storage_.isStored(id)) {
			return storage_.store(id, doCreate(id, std::forward<CreatorParams>(creatorParams)...));
		}
		return storage_.get(id);
    }

	template <class... CreatorParams>
    StoredInstance create(const IdentifierParam id, CreatorParams&&... creatorParams) volatile {
    	return lock()->create(id, std::forward<CreatorParams>(creatorParams)...);
    }

private:

    Storage storage_;

};

} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_FACTORY_HPP_ */
