#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_PARSEERROR_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_PARSEERROR_HPP_

#include <boost/filesystem/path.hpp>

#include "configuration/configuration-exceptions.hpp"

namespace coconut_tools {
namespace configuration {
namespace parsers {

class ParseError : public ConfigurationException {
public:

    ParseError(size_t theLineNo) :
        ConfigurationException(constructMessage(boost::filesystem::path(), theLineNo)),
        lineNo_(theLineNo) {
    }

    ParseError(const boost::filesystem::path& thePath, size_t theLineNo) :
        ConfigurationException(constructMessage(thePath, theLineNo)),
        path_(thePath),
        lineNo_(theLineNo) {
    }

    ParseError(const boost::filesystem::path& thePath, size_t theLineNo, const std::exception& cause) :
        ConfigurationException(constructMessage(thePath, theLineNo), cause),
        path_(thePath),
        lineNo_(theLineNo) {
    }

    ~ParseError() throw() {
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

} // namespace parsers
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_PARSEERROR_HPP_ */
