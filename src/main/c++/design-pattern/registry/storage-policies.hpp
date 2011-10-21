#ifndef COCONUTTOOLS_DESIGNPATTERN_REGISTRY_STORAGE_POLICIES_HPP_
#define COCONUTTOOLS_DESIGNPATTERN_REGISTRY_STORAGE_POLICIES_HPP_

#include <map>

#include <boost/call_traits.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#include "utils/Null.hpp"

namespace coconut_tools {
namespace design_pattern {
namespace registry {

template <class KeyType, class PlaceholderType>
class MapStoragePolicy {
public:

    typedef KeyType Key;

    typedef PlaceholderType Placeholder;

    typedef typename boost::call_traits<Key>::param_type KeyParam;

    std::pair<bool, Placeholder&> get(const KeyParam key) {
        typename Objects::Iterator it = objects_.lower_bound(key);

        if (it == objects_.end || it->first != key) {
            return std::make_pair(false, *objects_.insert(std::make_pair(key, Placeholder()), it)->second);
        } else {
            return std::make_pair(true, *it);
        }
    }

private:

    typedef std::map<Key, Placeholder> Objects;

    Objects objects_;

};

template <class KeyType, class PlaceholderType>
class SingletonStoragePolicy {
public:

    typedef KeyType Key;

    typedef PlaceholderType Placeholder;

    BOOST_STATIC_ASSERT(boost::is_same<Key, utils::Null>::value);

    SingletonStoragePolicy() :
        object_() {
    }

    std::pair<bool, Placeholder&> get(utils::Null) {
        return std::pair<bool, Placeholder&>(object_, object_);
    }

private:

    Placeholder object_;

};

} // namespace registry
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUTTOOLS_DESIGNPATTERN_REGISTRY_STORAGE_POLICIES_HPP_ */
