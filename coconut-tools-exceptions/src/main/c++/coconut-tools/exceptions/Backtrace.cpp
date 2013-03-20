#include "Backtrace.hpp"

using namespace coconut_tools::exceptions;

std::ostream& coconut_tools::exceptions::operator<< (std::ostream& os, const Backtrace& backtrace) {
    return backtrace.print(os);
}
