#ifndef COCONUT_TOOLS_UTILS_INITIALISABLE_HPP_
#define COCONUT_TOOLS_UTILS_INITIALISABLE_HPP_

#include <memory>

#include "Initialiser.hpp"

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

namespace coconut_tools {
namespace utils {

template <class ValueType, class... InitialiseArguments>
class Initialisable {
public:

	typedef ValueType Value;

	typedef Initialiser<Value, InitialiseArguments...> Initialiser;

protected:

	Initialisable() {
	}

	virtual ~Initialisable() {
	}

	void initialise(InitialiseArguments... arguments) {
		doInitialise(arguments...);
	}

	virtual void doInitialise(InitialiseArguments... arguments) = 0;

	friend class utils::Initialiser<Value, InitialiseArguments...>;

};

}  // namespace utils
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_INITIALISABLE_HPP_ */
