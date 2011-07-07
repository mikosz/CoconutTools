#ifndef COCONUTTOOLS_DESIGNPATTERN_REGISTRY_REGISTRY_HPP_
#define COCONUTTOOLS_DESIGNPATTERN_REGISTRY_REGISTRY_HPP_

#include <boost/noncopyable.hpp>

namespace CoconutTools {
namespace designPattern {
namespace registry {

template <class K, class V, template <class, class> class StoragePolicy>
class Registry : boost::noncopyable {

};

} // namespace registry
} // namespace designPattern
} // namespace CoconutTools

#endif /* COCONUTTOOLS_DESIGNPATTERN_REGISTRY_REGISTRY_HPP_ */
