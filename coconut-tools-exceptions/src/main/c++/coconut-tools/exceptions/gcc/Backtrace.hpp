#ifndef COCONUT_TOOLS_EXCEPTIONS_GCC_BACKTRACE_HPP_
#define COCONUT_TOOLS_EXCEPTIONS_GCC_BACKTRACE_HPP_

#include <string>
#include <vector>
#include <iosfwd>

namespace coconut_tools {
namespace exceptions {
namespace gcc {

class Backtrace {
public:

    class Frame {
    public:

        Frame(const std::string& mangledName);

        const std::string& name() const {
            return name_;
        }

    private:

        std::string name_;

    };

    typedef std::vector<Frame> Stack;

    Backtrace();

    const Stack& stack() const {
        return stack_;
    }

    std::ostream& print(std::ostream& os) const;

private:

    Stack stack_;

};

} // namespace gcc
} // namespace exceptions
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_EXCEPTIONS_GCC_BACKTRACE_HPP_ */
