#ifndef COCONUT_TOOLS_POLICY_CREATION_HPP_
#define COCONUT_TOOLS_POLICY_CREATION_HPP_

#include <memory>
#include <type_traits>

namespace coconut_tools {
namespace policy {
namespace creation {

template <class FunctionType, class... Arguments>
class Functor {
public:

    using Instance = std::result_of_t<FunctionType(Arguments...)>;

    Functor(FunctionType creator) :
        creator_(creator) {
    }

    Instance create(Arguments&&... arguments) {
        return creator_(std::forward<Arguments>(arguments)...);
    }

private:

    FunctionType creator_;

};

template <class... Arguments, class FunctionType>
Functor<FunctionType, Arguments...> makeFunctor(FunctionType creator) {
	return Functor<FunctionType, Arguments...>(std::move(creator));
}

} // namespace creation
} // namespace policy
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_POLICY_CREATION_HPP_ */
