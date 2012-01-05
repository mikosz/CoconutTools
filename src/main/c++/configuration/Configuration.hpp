#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/call_traits.hpp>
#include <boost/optional.hpp>
#include <boost/unordered_map.hpp>

#include "utils/Sequence.hpp"
#include "configuration-exceptions.hpp"
#include "Reader.hpp"

namespace coconut_tools {
namespace configuration {

class Configuration {
public:

    typedef boost::unordered_multimap<std::string, std::string> Values;

    Configuration(const Values& values) :
        values_(values) {
    }

    Configuration(const Reader& reader) {
        reader.read(values_);
    }

    template<class T>
    T getRequiredValue(const std::string& key) const {
        utils::Sequence<Values::const_iterator> range = getValues(key);
        if (range.atEnd()) {
            throw MissingRequiredValue(key);
        }
        Values::const_iterator it = range.current();
        range.next();
        if (!range.atEnd()) {
            throw MultipleValuesWhereSingleValueRequired(key);
        }
        return boost::lexical_cast<T>(it->second);
    }

    template<class T>
    boost::optional<T> getValue(const std::string& key, const boost::optional<T>& defaultValue =
            boost::optional<T>()) const {
        utils::Sequence<Values::const_iterator> range = getValues(key);
        if (range.atEnd()) {
            return defaultValue;
        }
        Values::const_iterator it = range.current();
        range.next();
        if (!range.atEnd()) {
            throw MultipleValuesWhereSingleValueRequired(key);
        }
        return boost::lexical_cast<T>(it->second);
    }

    utils::Sequence<Values::const_iterator> getValues(const std::string& key) const {
        return values_.equal_range(key);
    }

    void insert(const std::string& key, const std::string& value) {
        values_.insert(std::make_pair(key, value));
    }

    void replace(const std::string& key, const std::string& value) {
        remove(key);
        insert(key, value);
    }

    bool remove(const std::string& key) {
        return values_.erase(key);
    }

    bool has(const std::string& key) const {
        return values_.count(key);
    }

    size_t count(const std::string& key) const {
        return values_.count(key);
    }

    const Values& values() const {
        return values_;
    }

private:

    Values values_;

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_ */
