#ifndef COCONUT_TOOLS_DESIGN_PATTERN_CREATOR_FUNCTORCREATOR_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_CREATOR_FUNCTORCREATOR_HPP_

#include <memory>
#include <functional>

namespace coconut_tools {
namespace design_pattern {
namespace creator {

template <class InstanceType>
class FunctorCreator {
public:

    typedef InstanceType Instance;

    typedef std::function<Instance ()> Creator;

    FunctorCreator(Creator creator) :
        creator_(creator) {
    }

    Instance create() {
        return creator_();
    }

private:

    Creator creator_;

};

} // namespace creator
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_CREATOR_FUNCTORCREATOR_HPP_ */
