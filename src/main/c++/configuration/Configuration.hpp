#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_

#include <string>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/call_traits.hpp>
#include <boost/optional.hpp>

#include "configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {

class Configuration {
public:

    typedef std::map<std::string, std::string> Values;

    Configuration(const Values& values) :
        values_(values) {
    }

    template <class T>
    T get(const std::string& key) const {
        Values::const_iterator it = values_.find(key);
        if (it == values_.end()) {
            throw
        }
        return boost::lexical_cast<T>(it->second);
    }

    template <class T>


    template <class T>
    void set(const std::string& key, const typename boost::call_traits<T>::param_type value) {
        values_[key] = value;
    }

private:

    Values values_;

};

} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATION_HPP_ */
