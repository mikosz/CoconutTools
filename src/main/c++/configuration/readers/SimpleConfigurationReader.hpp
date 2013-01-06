#ifndef COCONUT_TOOLS_CONFIUGRATION_READERS_SIMPLECONFIGURATIONREADER_HPP_
#define COCONUT_TOOLS_CONFIUGRATION_READERS_SIMPLECONFIGURATIONREADER_HPP_

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "utils/pointee.hpp"

#include "configuration/parsers/SimpleParser.hpp"
#include "configuration/Configuration.hpp"

namespace coconut_tools {
namespace configuration {
namespace readers {

template <class Key, class Value>
class SimpleConfigurationReader {
public:

    void read(
            const parsers::SimpleParser& parser,
            std::istream& is,
            Configuration<Key, Value>* configurationParam
            ) {
        Configuration<Key, Value>& configuration = utils::pointee(configurationParam);

        parser.parse(is, boost::bind(&add_, _1, _2, &configuration));
    }

    void read(
            const parsers::SimpleParser& parser,
            const boost::filesystem::path& path,
            Configuration<Key, Value>* configurationParam
            ) {
        Configuration<Key, Value>& configuration = utils::pointee(configurationParam);

        parser.parse(path, boost::bind(&add_, _1, _2, &configuration));
    }

private:

    static void add_(
            const std::string& key,
            const std::string& value,
            Configuration<Key, Value>* configurationParam
            ) {
        Configuration<Key, Value>& configuration = utils::pointee(configurationParam);

        configuration.add(boost::lexical_cast<Key>(key), boost::lexical_cast<Value>(value));
    }

};

} // namespace readers
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIUGRATION_READERS_SIMPLECONFIGURATIONREADER_HPP_ */
