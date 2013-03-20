#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_HIERARCHICALPARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_HIERARCHICALPARSER_HPP_

#include <boost/filesystem/path.hpp>
#include <boost/function.hpp>

namespace coconut_tools {
namespace configuration {
namespace parsers {

class HierarchicalParser {
public:

	typedef boost::function<void (const std::string&)> NewChildCallback;

	typedef boost::function<void ()> ChildrenEndCallback;

	virtual ~HierarchicalParser() {
	}

	virtual void parse(std::istream& is, NewChildCallback newChildCallback,
			ChildrenEndCallback childrenEndCallback) const = 0;

	void parse(const boost::filesystem::path& path, NewChildCallback newChildCallback,
			ChildrenEndCallback childrenEndCallback) const;

};

}  // namespace parsers
}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_HIERARCHICALPARSER_HPP_ */
