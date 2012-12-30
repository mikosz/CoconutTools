#ifndef COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_

#include <algorithm>
#include <iterator>

#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "StringConfiguration.hpp"
#include "Reader.hpp"
#include "utils/Sequence.hpp"
#include "utils/pointee.hpp"
#include "utils/Extractor.hpp"

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

    typedef boost::unordered_multimap<typename Super::Key, typename Super::Value> Storage;

    FlatConfiguration() {
    }

    FlatConfiguration(const Storage& values) :
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

    typename Super::Value get(const typename Super::KeyParam key) const {
        utils::Sequence<typename Storage::const_iterator> range = values_.equal_range(key);
        if (range.atEnd()) {
            throw MissingRequiredValue(boost::lexical_cast<std::string>(key));
        }
        typename Storage::const_iterator it = range.current();
        range.next();
        if (!range.atEnd()) {
            throw MultipleValuesWhereSingleValueRequired(boost::lexical_cast<std::string>(key));
        }
        return it->second;
    }

    void getAll(
            const typename Super::KeyParam key,
            typename Super::Values* valuesParam
            ) const {
        typename Super::Values& values = *valuesParam;
        utils::Sequence<typename Storage::const_iterator> range = values_.equal_range(key);
        std::transform(
                range.pair().first,
                range.pair().second,
                std::back_inserter(values),
                boost::bind(utils::makeExtractor(&Storage::value_type::second), _1)
        );
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

    void keys(typename Super::Keys* keysParam) const {
        typename Super::Keys& k = utils::pointee(keysParam);
        std::transform(
                values_.begin(),
                values_.end(),
                std::inserter(k, k.end()),
                boost::bind(utils::makeExtractor(&Storage::value_type::first), _1)
        );
    }

private:

    Storage values_;

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_ */
