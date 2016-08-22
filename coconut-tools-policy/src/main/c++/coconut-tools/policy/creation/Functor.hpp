#ifndef COCONUT_TOOLS_POLICY_CREATION_HPP_
#define COCONUT_TOOLS_POLICY_CREATION_HPP_

#include <memory>
#include <functional>

namespace coconut_tools {
namespace policy {
namespace creation {

template <class InstanceType>
class Functor {
public:

    using Instance = InstanceType;

    using Creator = std::function<Instance ()>;

    FunctorCreator(Creator creator) :
        creator_(creator) {
    }

    Instance create() {
        return creator_();
    }

private:

    Creator creator_;

};

} // namespace creation
} // namespace policy
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_POLICY_CREATION_HPP_ */
