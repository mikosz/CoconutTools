#ifndef COCONUTTOOLS_DESIGNPATTERN_REGISTRY_STORAGE_POLICIES_HPP_
#define COCONUTTOOLS_DESIGNPATTERN_REGISTRY_STORAGE_POLICIES_HPP_

#include <map>

#include <boost/call_traits.hpp>

namespace CoconutTools {
namespace designPattern {
namespace registry {

template <class K, class V>
class MapStoragePolicy {
public:

    typedef K Key;

    typedef V Value;

    typedef typename boost::call_traits<K>::param_type KeyParam;

    typedef std::map<K, V> Objects;

    typedef typename Objects::iterator Iterator;

    std::pair<bool, Iterator> find(const KeyParam key) {
        Iterator it = objects_.lower_bound(key);

        bool found;

        if (it == objects_.end || it->first != key) {
            found = false;
        } else {
            found = true;
        }

        return std::make_pair(found, it);
    }

    void insert(const KeyParam key, V value, Iterator hint) {
        objects_.insert(std::make_pair(key, value), hint);
    }

private:

    Objects objects_;

};

} // namespace registry
} // namespace designPattern
} // namespace CoconutTools

#endif /* COCONUTTOOLS_DESIGNPATTERN_REGISTRY_STORAGE_POLICIES_HPP_ */
