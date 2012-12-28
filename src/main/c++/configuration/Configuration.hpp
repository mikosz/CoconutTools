#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_

#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/call_traits.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/ref.hpp>
#include <boost/unordered_set.hpp>
#include <boost/optional.hpp>

#include "configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {

/**
 * Generic configuration interface. Design to support both simple key-value configurations as well as
 * structured configurations, such as ones created by xml documents.
 */
template <class KeyType, class ValueType>
class Configuration {
private:

    struct ReferenceHash {
        size_t operator() (const boost::reference_wrapper<const KeyType> keyReference) const {
            return boost::hash_value(keyReference.get());
        }
    };

    struct ReferenceEqual {
        bool operator() (
                const boost::reference_wrapper<const KeyType> lhs,
                const boost::reference_wrapper<const KeyType> rhs
                ) const {
            return std::equal_to<KeyType>()(lhs.get(), rhs.get());
        }
    };

public:

    typedef KeyType Key;

    typedef ValueType Value;

    typedef typename boost::call_traits<Key>::param_type KeyParam;

    typedef typename boost::call_traits<Value>::param_type ValueParam;

    typedef boost::unordered_set<boost::reference_wrapper<const Key>, ReferenceHash, ReferenceEqual> KeyRefs;

    typedef std::vector<boost::reference_wrapper<const Value> > ValueRefs;

    typedef boost::shared_ptr<Configuration<Key, Value> > Ptr;

    typedef boost::shared_ptr<const Configuration<Key, Value> > ConstPtr;

    virtual ~Configuration() {
    }

    /**
     * Clear the configuration.
     *
     * Postconditions: empty() == true
     */
    virtual void clear() = 0;

    /**
     * Inform whether the configuration is empty.
     *
     * @return bool - true iff for all keys k count(k) == 0.
     */
    virtual bool empty() const = 0;

    /**
     * Returns the number of occurences of the provided key in the configuration.
     *
     * @param key - the key to look for in the configuration
     * @return size_t - the number of occurences of key in the configuration
     */
    virtual size_t count(const KeyParam key) const = 0;

    /**
     * Returns a single value specified for the provided key. If none or multiple values are specified,
     * throws a relevant exception.
     *
     * @param key - the key to look for in the configuration
     * @return const Value& - the value specified for key
     * @throws MissingRequiredValue - iff count(key) == 0
     * @throws MultipleValuesWhereSingleValueRequired - iff count(key) > 0
     */
    virtual const Value& get(const KeyParam key) const = 0;

    /**
     * Returns all values specified for the provided key. Does not clear values beforehand.
     *
     * @param key - the key to look for in the configuration
     * @param values[out] - references to all the values specified for key
     */
    virtual void getAll(const KeyParam key, ValueRefs* values) const = 0;

    /**
     * Sets the value for the provided key, overwriting the existing values.
     *
     * Postcondition: get(key) == value
     */
    virtual void set(const KeyParam key, const ValueParam value) = 0;

    /**
     * Adds another value for the provided key.
     *
     * Precondition: count(key) == n
     * Postcondition: count(key) == n + 1 and getAll(key) contains value
     */
    virtual void add(const KeyParam key, const ValueParam value) = 0;

    /**
     * Remove all occurences of the provided key.
     *
     * Postcondition: count(key) == 0
     *
     * @param key - the key to look for in the configuration
     */
    virtual void erase(const KeyParam key) = 0;

    /**
     * Returns all the keys existing in the current configuration. Does not clear k beforehand.
     *
     * @param k[out] - a set of references to all keys in the current configuration
     */
    virtual void keys(KeyRefs* k) const = 0;

    /**
     * Returns the value specified for the given key or defaultValue if no value is specified.
     *
     * @param key - the key to look for in the configuration
     * @param defaultValue - the defaultValue which will be returned if count(key) == 0
     * @return boost::optional<const Value&> - the value specified for key, or defaultValue if count(key) == 0
     * @throws MultipleValuesWhereSingleValueRequired - iff count(key) > 0
     */
    boost::optional<const Value&> getOptional(const KeyParam key, boost::optional<const Value&> defaultValue =
            boost::optional<const Value&>()) {
        return count(key) ? get(key) : defaultValue;
    }

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_ */
