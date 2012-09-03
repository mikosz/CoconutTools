#ifndef COCONUT_TOOLS_CONFIGURATION_STRINGCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_STRINGCONFIGURATION_HPP_

#include "Configuration.hpp"
#include "utils/to-string.hpp"

namespace coconut_tools {
namespace configuration {

template <class StringType>
class StringConfiguration : public Configuration<StringType, StringType> {
public:

    template <class T>
    T getAs(const KeyParam key) const {
        return as<T>(key, get(key));
    }

    template <class C>
    void getAllAs(C* values, const KeyParam key) const {
        std::vector<boost::reference_wrapper<const Value> > sourceValues;
        getAll(&sourceValues, key);
        std::transform(sourceValues.begin(), sourceValues.end(), std::inserter(*values, values->end()),
                boost::bind(&as<typename C::value_type>, key, _1));
    }

private:

    template <class T>
    static T as(const KeyParam key, const ValueParam value) {
        try {
            return boost::lexical_cast<T>(value);
        } catch (const boost::bad_lexical_cast&) {
            throw BadValueType(utils::toString(key), utils::toString(value), static_cast<T*>(0));
        }
    }

};

namespace detail {

/**
 * Utility class for selecting a superclass for a configuration class. Configuration implementations may
 * specify StringConfigurationSuperclassTraits<Key, Value>::Super as their superclass. All implementations
 * that use string types as keys and values will then use StringConfiguration as their superclass thus
 * inheriting facilitating functions implemented for such types.
 */
template<class Key, class Value>
class StringConfigurationSuperclassTraits {
public:

    typedef Configuration<Key, Value> Super;

};

template<class Char, class Traits, class Alloc>
class StringConfigurationSuperclassTraits<std::basic_string<Char, Traits, Alloc>, std::basic_string<Char, Traits, Alloc> > {
public:

    typedef StringConfiguration<std::basic_string<Char, Traits, Alloc> > Super;

};

} // namespace detail

}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_STRINGCONFIGURATION_HPP_ */
