#ifndef COCONUT_TOOLS_CONFIGURATION_READERS_HIERARCHICALCONFIGURATIONREADER_HPP_
#define COCONUT_TOOLS_CONFIGURATION_READERS_HIERARCHICALCONFIGURATIONREADER_HPP_

#include <boost/filesystem/path.hpp>

#include "coconut-tools/configuration/parsers/HierarchicalParser.hpp"
#include "coconut-tools/configuration/HierarchicalConfiguration.hpp"

namespace coconut_tools {
namespace configuration {
namespace readers {

class HierarchicalConfigurationReader {
public:

    void read(
            const parsers::HierarchicalParser& parser,
            std::istream& is,
            HierarchicalConfiguration* configurationParam
            ) const;

    void read(
            const parsers::HierarchicalParser& parser,
            const boost::filesystem::path& path,
            HierarchicalConfiguration* configurationParam
            ) const;

};

} // namespace readers
} // namespace configuration
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_CONFIGURATION_READERS_HIERARCHICALCONFIGURATIONREADER_HPP_ */
