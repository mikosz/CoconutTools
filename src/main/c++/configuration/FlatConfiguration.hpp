#ifndef COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_

#include <algorithm>
#include <iterator>

#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>

#include "StringConfiguration.hpp"
#include "Reader.hpp"
#include "utils/Sequence.hpp"

namespace coconut_tools {
namespace configuration {

/**
 * Implements the Configuration interface for simple flat configurations. The configuration is stored in a
 * hash-multi-map.
 */
template<class KeyType, class ValueType>
class FlatConfiguration: public detail::StringConfigurationSuperclassTraits<KeyType, ValueType>::Super {
private:

    typedef typename detail::StringConfigurationSuperclassTraits<KeyType, ValueType>::Super Super;

public:

    typedef boost::unordered_multimap<typename Super::Key, typename Super::Value> Values;

    FlatConfiguration() {
    }

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

    size_t count(const typename Super::KeyParam key) const {
        return values_.count(key);
    }

    const typename Super::Value& get(const typename Super::KeyParam key) const {
        utils::Sequence<typename Values::const_iterator> range = values_.equal_range(key);
        if (range.atEnd()) {
            throw MissingRequiredValue(boost::lexical_cast<std::string>(key));
        }
        typename Values::const_iterator it = range.current();
        range.next();
        if (!range.atEnd()) {
            throw MultipleValuesWhereSingleValueRequired(boost::lexical_cast<std::string>(key));
        }
        return it->second;
    }

    void getAll(
            const typename Super::KeyParam key,
            typename Super::ValueRefs* values
            ) const {
        utils::Sequence<typename Values::const_iterator> range = values_.equal_range(key);
        std::transform(range.pair().first, range.pair().second, std::back_inserter(*values),
                &valueCRef);
    }

    void set(const typename Super::KeyParam key, const typename Super::ValueParam value) {
        erase(key);
        add(key, value);
    }

    void add(const typename Super::KeyParam key, const typename Super::ValueParam value) {
        values_.insert(std::make_pair(key, value));
    }

    void erase(const typename Super::KeyParam key) {
        values_.erase(key);
    }

    void keys(typename Super::KeyRefs* k) const {
        std::transform(values_.begin(), values_.end(), std::inserter(*k, k->end()), &keyCRef);
    }

private:

    Values values_;

    static boost::reference_wrapper<const typename Super::Key> keyCRef(
            const typename Values::value_type& value) {
        return boost::ref(value.first);
    }

    static boost::reference_wrapper<const typename Super::Value> valueCRef(
            const typename Values::value_type& value) {
        return boost::ref(value.second);
    }

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_ */
