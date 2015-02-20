#ifndef COCONUT_TOOLS_CONFIUGRATION_READERS_SIMPLECONFIGURATIONREADER_HPP_
#define COCONUT_TOOLS_CONFIUGRATION_READERS_SIMPLECONFIGURATIONREADER_HPP_

#include <functional>

#include <boost/lexical_cast.hpp>

#include "coconut-tools/utils/pointee.hpp"

#include "coconut-tools/configuration/parsers/FlatParser.hpp"
#include "coconut-tools/configuration/Configuration.hpp"

namespace coconut_tools {
namespace configuration {
namespace readers {

template <class Key, class Value>
class FlatConfigurationReader {
public:

    void read(
            const parsers::FlatParser& parser,
            std::istream& is,
            Configuration<Key, Value>* configurationParam
            ) const {
        Configuration<Key, Value>& configuration = utils::pointee(configurationParam);

        parser.parse(is, std::bind(&add_, std::placeholders::_1, std::placeholders::_2, &configuration));
    }

    void read(
            const parsers::FlatParser& parser,
            const boost::filesystem::path& path,
            Configuration<Key, Value>* configurationParam
            ) const {
        Configuration<Key, Value>& configuration = utils::pointee(configurationParam);

        parser.parse(path, std::bind(&add_, std::placeholders::_1, std::placeholders::_2, &configuration));
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
