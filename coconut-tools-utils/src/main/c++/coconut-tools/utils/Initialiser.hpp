#ifndef COCONUT_TOOLS_UTILS_INITIALISER_HPP_
#define COCONUT_TOOLS_UTILS_INITIALISER_HPP_

#include <memory>

#include <boost/noncopyable.hpp>

#include "coconut-tools/exceptions/LogicError.hpp"

namespace coconut_tools {
namespace utils {

class ObjectAlreadyInitialised : public exceptions::LogicError {
};

template <class InitialisableType, class... Arguments>
class Initialiser : boost::noncopyable {
public:

	typedef InitialisableType Initialisable;

	typedef std::unique_ptr<Initialisable> Ptr;

	template <class ConcreteType>
	static Initialiser createInitialisable() {
		return Initialiser(Ptr(new ConcreteType));
	}

	Initialiser(Ptr&& initialisable) :
		initialisable_(initialisable)
	{
	}

	Ptr initialise(Arguments... arguments) {
		if (!initialisable_) {
			throw ObjectAlreadyInitialised();
		}

		initialisable_->initialise(arguments...);
		return Ptr(initialisable_.release());
	}

private:

	Ptr initialisable_;

};

}  // namespace utils
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_INITIALISER_HPP_ */
