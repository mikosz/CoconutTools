#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_FACTORY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_FACTORY_HPP_

#include <unordered_map>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace design_pattern {
namespace factory {

template <class CreatorType>
class CreatorRegistry {
public:

	using Creator = CreatorType;

	void registerCreator(const IdentifierParam id, Creator creator) {
		typename Creators::iterator it = creators_.lower_bound(id);
		if (it != creators_.end() && it->first == id) {
			ErrorPolicy::alreadyRegistered(id);
		} else {
			creators_.insert(it, std::make_pair(id, creator));
		}
	}

	void unregisterCreator(const IdentifierParam id) {
		if (!creators_.erase(id)) {
			ErrorPolicy::noSuchType(id);
		}
	}

protected:

	auto doCreate(const IdentifierParam id) -> decltype(Creator(id)) {
		typename Creators::iterator it = creators_.find(id);
		if (it == creators_.end()) {
			ErrorPolicy::noSuchType(id);
			return StoredInstance();
		}
		return storage_.store(id, it->second.create());
	}

private:

	using Creators = std::unordered_map<Identifier, Creator>;

	Creators creators_;

};

template <
    class IdentifierType,
    class InstanceType,
    template<class /* IdentifierType */, class /* InstanceType */> class StorageType,
    class CreationPolicy,
    class LockingPolicyType,
    template<class /* IdentifierType */> class ErrorPolicyType
    >
class Factory : public CreationPolicy {
public:

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    typedef InstanceType Instance;

    typedef LockingPolicyType LockingPolicy;

    typedef StorageType<Identifier, Instance> Storage;

    typedef typename Storage::Permanent StoredInstance;

    typedef ErrorPolicyType<Identifier> ErrorPolicy;

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
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_FACTORY_HPP_ */
