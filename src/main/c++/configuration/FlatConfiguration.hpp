#ifndef COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_

#include <algorithm>
#include <iterator>

#include <boost/unordered_map.hpp>

#include "StringConfiguration.hpp"
#include "Reader.hpp"

namespace coconut_tools {
namespace configuration {

/**
 * Implements the Configuration interface for simple flat configurations. The configuration is stored in a
 * hash-multi-map.
 */
template<class KeyType, class ValueType>
class FlatConfiguration: public detail::StringConfigurationSuperclassTraits<KeyType, ValueType>::Super {
public:

    typedef boost::unordered_multimap<Key, Value> Values;

    FlatConfiguration(const Values& values) :
        values_(values) {
    }

    FlatConfiguration(const Reader& reader) {
        reader.read(values_);
    }

    void clear() {
        values_.clear();
    }

    bool empty() const {
        return values_.empty();
    }

    size_t count(const KeyParam key) const {
        return values_.count(key);
    }

    const Value& get(const KeyParam key) const {
        utils::Sequence<Values::const_iterator> range = getValues(key);
        if (range.atEnd()) {
            throw MissingRequiredValue(key);
        }
        Values::const_iterator it = range.current();
        range.next();
        if (!range.atEnd()) {
            throw MultipleValuesWhereSingleValueRequired(key);
        }
        return it->second;
    }

    void getAll(const KeyParam key, std::vector<boost::reference_wrapper<const Value> >* values) const {
        std::pair<Values::const_iterator, Values::const_iterator> range = values_.equal_range(key);
        std::transform(range.first, range.second, std::back_inserter(*values), &boost::ref<const Value>);
    }

    void set(const KeyParam key, const ValueParam value) {
        erase(key);
        add(key, value);
    }

    void add(const KeyParam key, const ValueParam value) {
        values_.insert(std::make_pair(key, value));
    }

    bool erase(const KeyParam key) {
        return values_.erase(key);
    }

    void keys(boost::unordered_set<boost::reference_wrapper<const Key> >* k) const {
        std::transform(values_.begin(), values_.end(), std::back_inserter(*k), &keyCRef);
    }

private:

    Values values_;

    static boost::reference_wrapper<const Key> keyCRef(const Values::value_type& value) {
        return boost::ref(value.first);
    }

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_ */
