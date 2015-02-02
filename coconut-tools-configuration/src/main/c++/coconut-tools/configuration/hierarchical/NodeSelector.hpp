#ifndef _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTOR_HPP_
#define _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTOR_HPP_

#include <boost/noncopyable.hpp>

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

namespace coconut_tools {
namespace configuration {

class HierarchicalConfiguration;

namespace hierarchical {

class NodeSelector : boost::noncopyable {
public:

	virtual ~NodeSelector() {
	}

	bool operator==(const NodeSelector& other) const {
		return selectorType() == other.selectorType() && equals(other);
	}

	virtual bool matches(const HierarchicalConfiguration& node) const = 0;

protected:

	enum Type {
		IS,
		HAS,
	};

	NodeSelector() {
	}

	virtual Type selectorType() const = 0;

	virtual bool equals(const NodeSelector& other) const = 0;

};

CT_SMART_POINTER_DEFINITONS(NodeSelector);

} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODESELECTOR_HPP_ */