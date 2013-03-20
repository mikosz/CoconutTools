#include "FlatParser.hpp"

#include <fstream>

#include "ParseError.hpp"

using namespace coconut_tools::configuration::parsers;

void FlatParser::parse(const boost::filesystem::path& path, KeyValueCallback keyValueCallback) const {
    std::ifstream ifs(path.string().c_str());
    try {
        parse(ifs, keyValueCallback);
        ifs.close();
    } catch (const ParseError& e) {
        throw ParseError(path, e.lineNo(), e);
    }
}
