#ifndef COCONUTTOOLS_DESIGNPATTERN_REGISTRY_REGISTRY_HPP_
#define COCONUTTOOLS_DESIGNPATTERN_REGISTRY_REGISTRY_HPP_

#include <boost/noncopyable.hpp>

namespace CoconutTools {
namespace design_pattern {
namespace registry {

template <class K, class V, template <class, class> class StoragePolicy, class LockingPolicy>
class Registry : boost::noncopyable {
public:

    typedef typename boost::call_traits<K>::param_type KeyParam;

    static V& instance(const KeyParam key);

private:

    typedef StoragePolicy<K, V> Storage;

    typedef typename LockingPolicy::Lock Lock;

    static Storage* storage_;

    static Storage& storage();

};

template <class K, class V, template <class, class> class SP, class LP>
SP<K, V>* Registry::storage_ = 0;

template <class K, class V, template <class, class> class SP, class LP>
SP<K, V>& Registry::storage() {
    if (!storage_) {
        storage_ = new Storage;
    }
}

template <class K, class V, template <class, class> class SP, class LP>
Registry

} // namespace registry
} // namespace design_pattern
} // namespace CoconutTools

#endif /* COCONUTTOOLS_DESIGNPATTERN_REGISTRY_REGISTRY_HPP_ */
