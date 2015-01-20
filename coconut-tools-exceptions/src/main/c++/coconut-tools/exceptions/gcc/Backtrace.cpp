#include "coconut-tools/system/platform.hpp"

#if defined(COMPILER_GCC)

#include "Backtrace.hpp"

#include <execinfo.h>
#include <cxxabi.h>

#include <sstream>
#include <ostream>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <iomanip>

#include <boost/bind.hpp>

#include "coconut-tools/utils/raii-helper.hpp"

using namespace coconut_tools::exceptions::gcc;

namespace {

const size_t BASE_STACK_SIZE = 64;
const size_t STACK_SIZE_INCREMENT = 32;

void addressStack(std::vector<void*>& stack) {
    stack.resize(BASE_STACK_SIZE);
    bool fullStack = false;
    while (!fullStack) {
        int size = backtrace(&stack.front(), stack.size());
        if (size >= stack.size()) {
            stack.resize(stack.size() + STACK_SIZE_INCREMENT);
        } else {
            fullStack = true;
            stack.resize(size);
        }
    }
}

void constructBacktrace(Backtrace::Stack& stack) {
    std::vector<void*> addrStack;
    addressStack(addrStack);

    char** stackSymbols = backtrace_symbols(&addrStack.front(), addrStack.size());
    coconut_tools::utils::RaiiHelper freeStackSymbols(boost::bind(&std::free, stackSymbols));

    if (stackSymbols) {
        for (size_t i = 0; i < addrStack.size(); ++i) {
            stack.push_back(Backtrace::Frame(stackSymbols[i]));
        }
    }
}

std::string demangle(const std::string& mangledName) {
    std::string::size_type start, end;
    start = mangledName.find('(');
    if (start == std::string::npos) {
        return mangledName;
    }
    ++start;
    end = mangledName.find('+', start);
    if (end == std::string::npos) {
        return mangledName;
    }

    int status;
    char* demangled = abi::__cxa_demangle(mangledName.substr(start, end - start).c_str(), 0, 0, &status);
    coconut_tools::utils::RaiiHelper freeDemangled(boost::bind(&std::free, demangled));
    if (status != 0) {
        return mangledName;
    }

    return demangled;
}

std::string printFrame(const Backtrace::Frame& frame, size_t& index) {
    std::ostringstream oss;
    oss << "#" << std::setw(3) << std::left << index++ << " " << frame.name();
    return oss.str();
}

} // anonymous namespace

Backtrace::Frame::Frame(const std::string& mangledName) :
    name_(demangle(mangledName)) {
}

Backtrace::Backtrace() {
    constructBacktrace(stack_);
}

std::ostream& Backtrace::print(std::ostream& os) const {
    std::ostringstream oss;
    size_t index = 0;
    std::transform(stack_.begin(), stack_.end(), std::ostream_iterator<std::string>(os, "\n"),
            boost::bind(&printFrame, _1, boost::ref(index)));
    return os << oss.str();
}

#endif /* COMPILER_GCC */
