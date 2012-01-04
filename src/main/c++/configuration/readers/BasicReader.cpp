#include "BasicReader.hpp"

#include <utils/Sequence.hpp>

using namespace coconut_tools::configuration::readers;

void BasicReader::read(Values& values) const {
    utils::Sequence<Parser::ParsedConfiguration::ConstIterator> in(parsedConfiguration_.begin(),
            parsedConfiguration_.end());
    while (!in.atEnd()) {
        values.insert(*in.current());
        in.next();
    }
}
