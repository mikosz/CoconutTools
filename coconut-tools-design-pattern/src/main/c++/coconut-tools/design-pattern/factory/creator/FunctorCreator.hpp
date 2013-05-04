#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_FUNCTORCREATOR_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_FUNCTORCREATOR_HPP_

#include <memory>

#include <boost/function.hpp>

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace creator {

template <class InstanceType>
class FunctorCreator {
public:

    typedef InstanceType Instance;

    typedef boost::function<std::auto_ptr<Instance>()> Creator;

    FunctorCreator(Creator creator) :
        creator_(creator) {
    }

    std::auto_ptr<Instance> create() {
        return creator_();
    }

private:

    Creator creator_;

};

} // namespace creator
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_FUNCTORCREATOR_HPP_ */
