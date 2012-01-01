#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/call_traits.hpp>
#include <boost/optional.hpp>
#include <boost/unordered_map.hpp>

#include "configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {

class Configuration {
public:

    typedef boost::unordered_map<std::string, std::string> Values;

    Configuration(const Values& values) :
        values_(values) {
    }

    template<class T>
    T getRequired(const std::string& key) const {
        Values::const_iterator it = values_.find(key);
        if (it == values_.end()) {
            throw MissingRequiredValue(key);
        }
        return boost::lexical_cast<T>(it->second);
    }

    template<class T>
    boost::optional<T> get(const std::string& key, const boost::optional<T>& defaultValue =
            boost::optional<T>()) const {
        Values::const_iterator it = values_.find(key);
        if (it == values_.end()) {
            return defaultValue;
        }
        return boost::lexical_cast<T>(it->second);
    }

    void set(const std::string& key, const std::string& value) {
        Values::iterator it = values_.find(key);
        if (it == values_.end()) {
            values_.insert(std::make_pair(key, value));
        } else {
            it->second = value;
        }
    }

    bool unset(const std::string& key) {
        return values_.erase(key);
    }

    bool has(const std::string& key) const {
        return values_.count(key);
    }

private:

    Values values_;

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_ */
