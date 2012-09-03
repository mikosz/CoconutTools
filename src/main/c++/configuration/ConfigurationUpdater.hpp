#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURATIONUPDATER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURATIONUPDATER_HPP_

#include <cstdlib>

#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

namespace coconut_tools {
namespace configuration {

template <class ConfigurationType>
class ConfigurationUpdater {
public:

    typedef ConfigurationType Configuration;

    typedef boost::function<void (const Configuration&)> VerifyFunc;

    typedef boost::function<void (const Configuration&)> UpdateFunc;

    typedef void* Listener;

    ~ConfigurationUpdater() {
        if (!listeners_.empty()) {
            // This is a serious logic error which would cause a segmentation fault.
            // Not throwing an exception as this is a destructor.
            std::abort();
        }
    }

    void registerListener(Listener listener, VerifyFunc verify, UpdateFunc update) {
        listeners_.insert(std::make_pair(listener, ListenerEntry(verify, update)));
    }

    void unregisterListener(Listener listener) {
        listeners_.erase(listener);
    }

    void update(const Configuration& configuration) {
        Listeners::iterator it, end = listeners_.end();
        for (it = listeners_.begin(); it != end; ++it) {
            it->second.verify(configuration);
        }
        for (it = listeners_.begin(); it != end; ++it) {
            it->second.update(configuration);
        }
    }

private:

    struct ListenerEntry {

        VerifyFunc verify;

        UpdateFunc update;

        ListenerEntry(VerifyFunc verify, UpdateFunc update) :
            verify(verify),
            update(update) {
        }

    };

    typedef boost::unordered_map<Listener, ListenerEntry> Listeners;

    Listeners listeners_;

};

}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURATIONUPDATER_HPP_ */
