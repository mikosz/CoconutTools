#ifndef COCONUT_TOOLS_CONFIGURATION_PARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSER_HPP_

#include <string>
#include <utility>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "utils/Sequence.hpp"
#include "configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {

class ParseError : public ConfigurationException {
public:

    EXCEPTION_CONSTRUCTORS(ParseError, ConfigurationException)

};

class Parser {
public:

    class ParsedConfiguration {
    public:

        typedef std::vector<std::pair<std::string, std::string> > Values;

        typedef Values::const_iterator ConstIterator;

        ParsedConfiguration(boost::shared_ptr<const Values> values) :
            values_(values) {
        }

        ConstIterator begin() const {
            return values_->begin();
        }

        ConstIterator end() const {
            return values_->end();
        }

    private:

        boost::shared_ptr<const Values> values_;

    };


    virtual ParsedConfiguration parse() const = 0;

};

}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSER_HPP_ */
