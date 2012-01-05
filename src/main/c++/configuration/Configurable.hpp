#ifndef COCONUT_TOOLS_CONFIGURATION_CONFIGURABLE_HPP_
#define COCONUT_TOOLS_CONFIGURATION_CONFIGURABLE_HPP_

#include <boost/bind.hpp>

#include "ConfigurationUpdater.hpp"

namespace coconut_tools {
namespace configuration {

class Configurable {
protected:

    Configurable(ConfigurationUpdater& configurationUpdater) :
        configurationUpdater_(configurationUpdater) {
        configurationUpdater_.registerListener(
                this,
                boost::bind(&Configurable::verify, this, _1),
                boost::bind(&Configurable::update, this, _1));
    }

    virtual ~Configurable() {
        configurationUpdater_.unregisterListener(this);
    }

    virtual void verify(const Configuration& config) const = 0;

    virtual void update(const Configuration& config) = 0;

private:

    ConfigurationUpdater& configurationUpdater_;

};

}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_CONFIGURABLE_HPP_ */
