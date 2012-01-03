#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_

#include <boost/filesystem/path.hpp>

#include "configuration/Parser.hpp"

namespace coconut_tools {
namespace configuration {
namespace parsers {

class ParsePropertiesError : public ParseError {
public:

    ParsePropertiesError(const boost::filesystem::path& thePath, size_t theLineNo) :
        ParseError(constructMessage(thePath, theLineNo)),
        path_(thePath),
        lineNo_(theLineNo) {
    }

    ~ParsePropertiesError() throw() {
    }

    const boost::filesystem::path& path() const {
        return path_;
    }

    size_t lineNo() const {
        return lineNo_;
    }

private:

    boost::filesystem::path path_;

    size_t lineNo_;

    static std::string constructMessage(const boost::filesystem::path& thePath, size_t theLineNo);

};

class PropertiesParser : public Parser {
public:

    PropertiesParser(const boost::filesystem::path& path) :
        path_(path) {
    }

    ParsedConfiguration parse() const;

private:

    boost::filesystem::path path_;

};

}  // namespace parsers
}  // namespace configuration
}  // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_PROPERTIESPARSER_HPP_ */
