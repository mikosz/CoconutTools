#ifndef COCONUT_TOOLS_CONFIGURATION_STACKEDCONFIGURATION_HPP_
#define COCONUT_TOOLS_CONFIGURATION_STACKEDCONFIGURATION_HPP_

#include <deque>

#include <boost/unordered_set.hpp>
#include <boost/bind.hpp>

#include "StringConfiguration.hpp"

namespace coconut_tools {
namespace configuration {

/**
 * StackedConfiguration stores the configuration in layers. Layers on top of others override values specified
 * on lower levels. This functionality may be used to create a configuration that is loaded from several
 * sources, for instance: default values < global file < local file < command line < environment variables.
 * All write operations on the configuration are performed on the topmost layer. As a result, if the layer is
 * popped, all changes are discarded. Read operations are performed top-down. If a value is specified or
 * erased on the current level, the search is stopped and the value(s) returned.
 */
template <class KeyType, class ValueType>
class StackedConfiguration : public detail::StringConfigurationSuperclassTraits<KeyType, ValueType>::Super {
public:

    void push(Ptr layer) {
        stack_.push_back(layer);
    }

    void pop() {
        // TODO: underflow?
        stack_.pop_back();
    }

    void flatten(Ptr target) {
        boost::unordered_set<boost::reference_wrapper<const Key> > k;
        keys(&k);
        std::for_each(k.begin(), k.end(), boost::bind(&copyAll, this, _1, target));
        stack_.clear();
        push(target);
    }

    void clear() {
        Layer& top = stack_.back();
        boost::unordered_set<boost::reference_wrapper<const Key> > k;
        top.configuration_->keys(&k);
        std::copy(k.begin(), k.end(), std::inserter(top.removed_, top.removed_.end()));
        top.configuration_->clear();
    }

    bool empty() {
        boost::unordered_set<boost::reference_wrapper<const Key> > k;
        keys(&k);
        return k.empty();
    }

    size_t count(const KeyParam key) const {
        return firstWith<size_t>(key, boost::bind(&Configuration::count, _1));
    }

private:

    class Layer {
    private:

        Layer(Ptr configuration) :
            configuration_(configuration) {
        }

        Ptr configuration_;

        boost::unordered_set<KeyType> removed_;

    };

    typedef std::deque<Layer> Stack;

    Stack stack_;

    template <class ReturnType>
    ReturnType firstWith(const KeyParam key, ReturnType defaultValue, boost::function<ReturnType (Ptr)>) const {
        Stack::const_iterator it, end = stack_.end();
        for (it = stack_.begin(); it != end; ++it) {
            if (it->count())
        }
        return defaultValue;
    }

    void copyAll(Key key, Ptr target) {
        std::vector<boost::reference_wrapper<const Value> > values;
        getAll(key, &values);
        std::for_each(values.begin(), values.end(), boost::bind(&Configuration::add, target, _1));
    }

};

}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_STACKEDCONFIGURATION_HPP_ */
