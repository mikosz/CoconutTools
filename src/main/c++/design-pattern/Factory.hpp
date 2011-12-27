#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_HPP_

#include <map>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace design_pattern {

class ExceptionThrowingErrorPolicy {
public:

    template <class T>
    static void alreadyRegistered(const T& id) {
        // xxx: !!!
        throw "abc";
    }

    template <class T>
    static void noSuchType(const T& id) {
        // xxx: !!!
        throw "abc";
    }

};

template <class IdentifierType, class InstanceType, class CreatorType, class ErrorPolicy>
class Factory {
public:

    typedef CreatorType Creator;

    typedef InstanceType Instance;

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    Instance create(const IdentifierParam id) {
        typename Creators::iterator it = creators_.find(id);
        if (it == creators_.end()) {
            ErrorPolicy::noSuchType(id);
        }
        return (it->second)();
    }

    void registerCreator(const IdentifierParam id, Creator creator) {
        typename Creators::iterator it = creators_.lower_bound(id);
        if (it != creators_.end() && it->first == id) {
            ErrorPolicy::alreadyRegistered(id);
        }
        creators_.insert(it, std::make_pair(id, creator));
    }

    void unregisterCreator(const IdentifierParam id) {
        if (!creators_.erase(id)) {
            ErrorPolicy::noSuchType(id);
        }
    }

private:

    typedef std::map<Identifier, Creator> Creators;

    Creators creators_;

};

} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_HPP_ */
