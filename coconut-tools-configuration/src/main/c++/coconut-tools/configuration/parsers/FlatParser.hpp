#ifndef COCONUT_TOOLS_CONFIGURATION_PARSERS_SIMPLEPARSER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_PARSERS_SIMPLEPARSER_HPP_

#include <iosfwd>
#include <functional>

#include <boost/filesystem/path.hpp>

namespace coconut_tools {
namespace configuration {
namespace parsers {

class FlatParser {
public:

    typedef std::function<void (const std::string&, const std::string&)> KeyValueCallback;

    virtual ~FlatParser() {
    }

    virtual void parse(std::istream& is, KeyValueCallback keyValueCallback) const = 0;

    void parse(const boost::filesystem::path& path, KeyValueCallback keyValueCallback) const;

};

} // namespace parsers
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_PARSERS_SIMPLEPARSER_HPP_ */
