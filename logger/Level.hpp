#ifndef COCONUTTOOLS_LOGGER_LEVEL_HPP_
#define COCONUTTOOLS_LOGGER_LEVEL_HPP_

namespace CoconutTools {
namespace logger {

class Level {
public:

    enum Value {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    Level(Value value) :
        value_(value) {
    }

    operator Value() const {
        return value_;
    }

    operator Value&() {
        return value_;
    }

private:

    Value value_;

};

}  // namespace logger
}  // namespace CoconutTools

#endif /* COCONUTTOOLS_LOGGER_LEVEL_HPP_ */
