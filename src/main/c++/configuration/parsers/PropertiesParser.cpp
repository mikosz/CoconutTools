#include "PropertiesParser.hpp"

#include <string>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace coconut_tools::configuration::parsers;

namespace {

const boost::regex EMPTY_LINE_REGEX("^\\s*(#.*)?$");
const boost::regex CATEGORY_REGEX("^\\s*\\[([^\\]]+)\\]\\s*$");
const boost::regex VALUE_REGEX("^([^=]+)=(.*)$");

} // anonymous namespace

std::string ParsePropertiesError::constructMessage(const boost::filesystem::path& thePath, size_t theLineNo) {
    std::ostringstream oss;
    oss << "Error while reading properties file " << thePath << " in line " << theLineNo;
    return oss.str();
}

PropertiesParser::ParsedConfiguration PropertiesParser::parse() const {
    boost::shared_ptr<ParsedConfiguration::Values> vals(new ParsedConfiguration::Values);

    std::ifstream ifs(path_.string().c_str());
    std::string line;
    size_t lineNo = 0;
    std::string categoryPrefix;

    while (std::getline(ifs, line)) {
        ++lineNo;
        boost::smatch matches;
        if (boost::regex_match(line, EMPTY_LINE_REGEX)) {
        } else if (boost::regex_match(line, matches, CATEGORY_REGEX)) {
            categoryPrefix = matches[1] + ".";
        } else if (boost::regex_match(line, matches, VALUE_REGEX)) {
            std::string key = boost::trim_copy(matches[1].str());
            std::string value = boost::trim_copy(matches[2].str());
            vals->push_back(std::make_pair(categoryPrefix + key, value));
        } else {
            throw ParsePropertiesError(path_, lineNo);
        }
    }

    return ParsedConfiguration(vals);
}
