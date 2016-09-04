#ifndef COCONUT_TOOLS_POLICY_NEW_HPP_
#define COCONUT_TOOLS_POLICY_NEW_HPP_

#include <memory>

namespace coconut_tools {
namespace policy {
namespace creation {

template <class InstanceType, class... Arguments>
class New {
public:

	using Instance = std::unique_ptr<InstanceType>;

	template <class ConcreteType>
	static New makeCreator() {
		return New(std::make_shared<ConcreteDelegate<ConcreteType>>());
	}

	New() :
		delegate_(std::make_shared<ConcreteDelegate<InstanceType>>()) // TODO: why shared?
	{
	}

	Instance create(Arguments&&... arguments) {
		return delegate_->create(std::forward<Arguments>(arguments)...);
	}

private:

	class AbstractDelegate {
	public:

		virtual ~AbstractDelegate() {
		}

		virtual Instance create(Arguments&&... arguments) = 0;

	};

	template <class ConcreteType>
	class ConcreteDelegate : public AbstractDelegate {
	public:

		Instance create(Arguments&&... arguments) override {
			return std::make_unique<ConcreteType>(std::forward<Arguments>(arguments)...);
		}

	};

	New(std::shared_ptr<AbstractDelegate> delegate) :
		delegate_(delegate) {
	}

	std::shared_ptr<AbstractDelegate> delegate_;

};

} // namespace creation
} // namespace policy
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_POLICY_NEW_HPP_ */
