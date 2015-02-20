#ifndef COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_

#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <functional>

#include <boost/lexical_cast.hpp>

#include "StringConfiguration.hpp"
#include "coconut-tools/utils/Sequence.hpp"
#include "coconut-tools/utils/pointee.hpp"
#include "coconut-tools/utils/Extractor.hpp"

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

    typedef std::unordered_multimap<typename Super::Key, typename Super::Value> Storage;

    FlatConfiguration() {
    }

    FlatConfiguration(const Storage& values) :
        values_(values) {
    }

    void clear() override {
        values_.clear();
    }

    bool empty() const override {
        return values_.empty();
    }

    size_t count(const typename Super::KeyParam key) const override {
        return values_.count(key);
    }

    typename Super::Value get(const typename Super::KeyParam key) const override {
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
            ) const override {
        typename Super::Values& values = *valuesParam;
        utils::Sequence<typename Storage::const_iterator> range = values_.equal_range(key);
        std::transform(
                range.pair().first,
                range.pair().second,
                std::back_inserter(values),
                std::bind(utils::makeExtractor(&Storage::value_type::second), std::placeholders::_1)
        );
    }

    void set(const typename Super::KeyParam key, const typename Super::ValueParam value) override {
        erase(key);
        add(key, value);
    }

    void add(const typename Super::KeyParam key, const typename Super::ValueParam value) override {
        values_.insert(std::make_pair(key, value));
    }

    void erase(const typename Super::KeyParam key) override {
        values_.erase(key);
    }

    void keys(typename Super::Keys* keysParam) const override {
        typename Super::Keys& k = utils::pointee(keysParam);
        std::transform(
                values_.begin(),
                values_.end(),
                std::inserter(k, k.end()),
                std::bind(utils::makeExtractor(&Storage::value_type::first), std::placeholders::_1)
        );
    }

private:

    Storage values_;

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_FLATCONFIGURATION_HPP_ */
