#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_NEWCREATOR_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_NEWCREATOR_HPP_

#include <memory>

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace creator {

template <class InstanceType>
class NewCreator {
public:

    typedef InstanceType Instance;

    std::auto_ptr<Instance> create() {
        return std::auto_ptr<Instance>(new Instance);
    }

};

} // namespace creator
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_NEWCREATOR_HPP_ */
