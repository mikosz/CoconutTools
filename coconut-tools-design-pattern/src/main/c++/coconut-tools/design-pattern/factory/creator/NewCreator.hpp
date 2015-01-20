#ifndef COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_NEWCREATOR_HPP_
#define COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_NEWCREATOR_HPP_

#include <memory>

#include <boost/shared_ptr.hpp>

namespace coconut_tools {
namespace design_pattern {
namespace factory {
namespace creator {

template <class InstanceType>
class NewCreator {
public:

    typedef InstanceType Instance;

    template <class ConcreteType>
    static NewCreator makeCreator();

    std::unique_ptr<Instance> create() {
    	return delegate_->create();
    }

private:

    class AbstractDelegate {
    public:

    	virtual ~AbstractDelegate() {
    	}

    	virtual std::unique_ptr<Instance> create() = 0;

    };

    template <class ConcreteType>
    class ConcreteDelegate : public AbstractDelegate {
    public:

    	std::unique_ptr<Instance> create() {
    		return std::unique_ptr<Instance>(new ConcreteType);
    	}

    };

    NewCreator(boost::shared_ptr<AbstractDelegate> delegate) :
    	delegate_(delegate) {
    }

    boost::shared_ptr<AbstractDelegate> delegate_;

};

template <class InstanceType>
template <class ConcreteType>
NewCreator<InstanceType> NewCreator<InstanceType>::makeCreator() {
	return NewCreator<InstanceType>(boost::shared_ptr<AbstractDelegate>(new ConcreteDelegate<ConcreteType>));
}

} // namespace creator
} // namespace factory
} // namespace design_pattern
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_DESIGN_PATTERN_FACTORY_CREATOR_NEWCREATOR_HPP_ */
