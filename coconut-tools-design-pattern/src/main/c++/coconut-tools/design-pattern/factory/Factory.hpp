#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_FACTORY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_FACTORY_HPP_

#include <map>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace design_pattern {
namespace factory {

template <
    class IdentifierType,
    class InstanceType,
    template<class /* IdentifierType */, class /* InstanceType */> class StorageType,
    class CreatorType,
    class LockingPolicyType,
    template<class /* IdentifierType */, class /* InstanceType */> class ErrorPolicyType
    >
class Factory {
public:

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    typedef InstanceType Instance;

    typedef CreatorType Creator;

    typedef LockingPolicyType LockingPolicy;

    typedef StorageType<Identifier, Instance> Storage;

    typedef typename Storage::Permanent StoredInstance;

    typedef ErrorPolicyType<Identifier, Instance> ErrorPolicy;

    StoredInstance create(const IdentifierParam id) {
        typename Storage::Permanent stored = storage_.get(id);
        if (stored.get()) {
            return stored;
        } else {
            typename Creators::iterator it = creators_.find(id);
            if (it == creators_.end()) {
                ErrorPolicy::noSuchType(id);
                return StoredInstance();
            }
            return storage_.store(id, it->second.create());
        }
    }

    StoredInstance create(const IdentifierParam id) volatile {
    	return lockingPolicy_.lock(this)->create(id);
    }

    void registerCreator(const IdentifierParam id, Creator creator) {
        typename Creators::iterator it = creators_.lower_bound(id);
        if (it != creators_.end() && it->first == id) {
            ErrorPolicy::alreadyRegistered(id);
        } else {
            creators_.insert(it, std::make_pair(id, creator));
        }
    }

    void registerCreator(const IdentifierParam id, Creator creator) volatile {
    	lockingPolicy_.lock(this)->registerCreator(id, creator);
    }

    void unregisterCreator(const IdentifierParam id) {
        if (!creators_.erase(id)) {
            ErrorPolicy::noSuchType(id);
        }
    }

    void unregisterCreator(const IdentifierParam id) volatile {
    	lockingPolicy_.lock(this)->unregisterCreator(id);
    }

private:

    typedef std::map<Identifier, Creator> Creators;

    LockingPolicy lockingPolicy_;

    Storage storage_;

    Creators creators_;

};

} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_FACTORY_HPP_ */
