#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_NOSTORAGE_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_NOSTORAGE_HPP_

#include <memory>

#include <boost/call_traits.hpp>

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace storage {

template <class IdentifierType, class InstanceType, class LockingPolicy>
class NoStorage {
public:

    typedef IdentifierType Identifier;

    typedef typename boost::call_traits<Identifier>::param_type IdentifierParam;

    typedef InstanceType Instance;

    typedef std::auto_ptr<Instance> InstanceParam;

    typedef std::auto_ptr<Instance> Stored;

    NoStorage(LockingPolicy*) {
    }

    Stored get(const IdentifierParam) const {
        return Stored();
    }

    Stored get(const IdentifierParam, LockingPolicy*) const volatile {
        return Stored();
    }

    bool isStored(const IdentifierParam) const {
        return false;
    }

    bool isStored(const IdentifierParam, LockingPolicy*) const volatile {
        return false;
    }

    Stored store(const IdentifierParam, InstanceParam instance) {
        return instance;
    }

    Stored store(const IdentifierParam, InstanceParam instance, LockingPolicy*) volatile {
        return instance;
    }

    void erase(const IdentifierParam) {
    }

    void erase(const IdentifierParam, LockingPolicy*) volatile {
    }

};

} // namespace storage
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_STORAGE_NOSTORAGE_HPP_ */
