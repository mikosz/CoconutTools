#ifndef COCONUT_TOOLS_CONFIGURATION_READER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_READER_HPP_

#include <string>

#include <boost/unordered_map.hpp>

namespace coconut_tools {
namespace configuration {

class Reader {
public:

    typedef boost::unordered_multimap<std::string, std::string> Values;

    virtual void read(Values& values) const = 0;

protected:

    virtual ~Reader() {
    }

};

}  // namespace configuration
}  // namespace coconut_tools#endif /* COCONUT_TOOLS_CONFIGURATION_READER_HPP_ */
