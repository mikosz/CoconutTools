#include "SimpleParser.hpp"

#include <fstream>

#include "ParseError.hpp"

using namespace coconut_tools::configuration::parsers;

void SimpleParser::parse(const boost::filesystem::path& path, KeyValueCallback keyValueCallback) const {
    std::ifstream ifs(path.string().c_str());
    try {
        parse(ifs, keyValueCallback);
        ifs.close();
    } catch (const ParseError& e) {
        throw ParseError(path, e.lineNo(), e);
    }
}
