#ifndef COCONUT_TOOLS_CONFIGURATION_READERS_BASICREADER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_READERS_BASICREADER_HPP_

#include "configuration/Reader.hpp"
#include "configuration/Parser.hpp"

namespace coconut_tools {
namespace configuration {
namespace readers {

class BasicReader : public Reader {
public:

    BasicReader(const Parser& parser) :
        parsedConfiguration_(parser.parse()) {
    }

    void read(Values& values) const;

private:

    Parser::ParsedConfiguration parsedConfiguration_;

};

}  // namespace readers
}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_READERS_BASICREADER_HPP_ */
