#ifndef COCONUT_TOOLS_POLICY_NEW_HPP_
#define COCONUT_TOOLS_POLICY_NEW_HPP_

#include <memory>

namespace coconut_tools {
namespace policy {
namespace creation {

template <class InstanceType, class... Arguments>
class New {
public:

	using Instance = InstanceType;

	template <class ConcreteType>
	static NewCreator makeCreator() {
		return NewCreator(std::make_shared<ConcreteDelegate<ConcreteType>>());
	}

	NewCreator() :
		delegate_(std::make_shared<ConcreteDelegate<Instance>>())
	{
	}

	std::unique_ptr<Instance> create(Arguments... arguments) {
		return delegate_->create(arguments...);
	}

private:

	class AbstractDelegate {
	public:

		virtual ~AbstractDelegate() {
		}

		virtual std::unique_ptr<Instance> create(Arguments... arguments) = 0;

	};

	template <class ConcreteType>
	class ConcreteDelegate : public AbstractDelegate {
	public:

		std::unique_ptr<Instance> create(Arguments... arguments) override {
			return std::unique_ptr<Instance>(new ConcreteType(arguments...));
		}

	};

	NewCreator(std::shared_ptr<AbstractDelegate> delegate) :
		delegate_(delegate) {
	}

	std::shared_ptr<AbstractDelegate> delegate_;

};

} // namespace creation
} // namespace policy
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_POLICY_NEW_HPP_ */
