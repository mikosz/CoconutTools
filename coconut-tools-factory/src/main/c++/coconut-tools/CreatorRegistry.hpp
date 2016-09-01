#ifndef COCONUT_TOOLS_FACTORY_CREATORREGISTRY_HPP_
#define COCONUT_TOOLS_FACTORY_CREATORREGISTRY_HPP_

namespace coconut_tools {
namespace factory {

template <class CreationPolicy>
class CreatorRegistry {
public:

	void registerCreationPolicy(const IdentifierParam id, CreationPolicy creator) {
		typename CreationPolicies::iterator it = creators_.lower_bound(id);
		if (it != creators_.end() && it->first == id) {
			ErrorPolicy::alreadyRegistered(id);
		} else {
			creators_.insert(it, std::make_pair(id, creator));
		}
	}

	void unregisterCreationPolicy(const IdentifierParam id) {
		if (!creators_.erase(id)) {
			ErrorPolicy::noSuchType(id);
		}
	}

protected:

	auto doCreate(const IdentifierParam id) -> decltype(CreationPolicy(id)) {
		typename CreationPolicys::iterator it = creators_.find(id);
		if (it == creators_.end()) {
			ErrorPolicy::noSuchType(id);
			return StoredInstance();
		}
		return storage_.store(id, it->second.create());
	}

private:

	using CreationPolicies = std::unordered_map<Identifier, CreationPolicy>;

	CreationPolicies creators_;

};

} // namespace factory
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_FACTORY_CREATORREGISTRY_HPP_ */
