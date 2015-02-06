#ifndef _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_SELECTOR_HPP_
#define _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_SELECTOR_HPP_

#include <iosfwd>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>

#include "coconut-tools/utils/smart-pointer-definitions.hpp"

namespace coconut_tools {
namespace configuration {
namespace hierarchical {

class HierarchicalConfiguration;

namespace node {

class Selector :
	boost::equality_comparable<Selector>,
	boost::noncopyable
{
public:

	virtual ~Selector() {
	}

	bool operator==(const Selector& other) const {
		return selectorType() == other.selectorType() && equals(other);
	}

	virtual bool matches(const HierarchicalConfiguration& node) const = 0;

	virtual std::string string() const = 0;

protected:

	enum Type {
		IS,
		HAS,
	};

	Selector() {
	}

	virtual Type selectorType() const = 0;

	virtual bool equals(const Selector& other) const = 0;

};

std::ostream& operator<<(std::ostream& os, const Selector& selector);

CT_SMART_POINTER_DEFINITONS(Selector);

} // namespace node
} // namespace hierarchical
} // namespace configuration
} // namespace coconut_tools

#endif /* _COCONUT_TOOLS_CONFIGURATION_HIERARCHICAL_NODE_SELECTOR_HPP_ */
