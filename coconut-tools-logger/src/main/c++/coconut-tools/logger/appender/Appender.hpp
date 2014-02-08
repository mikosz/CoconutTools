#ifndef COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_
#define COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_

#include <iosfwd>
#include <string>

#include <boost/shared_ptr.hpp>

#include "../layout/Layout.hpp"
#include "../Context.hpp"

namespace coconut_tools {
namespace logger {
namespace appender {

class Appender {
public:

    virtual ~Appender() {
    }

    void append(Level level, const Context& context, const std::string& message);

protected:

    virtual void doAppend(const std::string& message) = 0;

    Appender() {
    }

	Appender(layout::LayoutPtr layout) :
		layout_(layout) {
	}

private:

    layout::LayoutPtr layout_;

};

typedef boost::shared_ptr<Appender> AppenderPtr;

} // namespace appender
} // namespace logger
} // namespace coconut_tools

#endif /* COCONUTTOOLS_LOGGER_APPENDER_APPENDER_HPP_ */
