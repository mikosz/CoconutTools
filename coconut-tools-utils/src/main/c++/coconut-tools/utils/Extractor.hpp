#ifndef COCONUT_TOOLS_UTILS_EXTRACTOR_HPP_
#define COCONUT_TOOLS_UTILS_EXTRACTOR_HPP_

#include <functional>

namespace coconut_tools {
namespace utils {

template <class Owner, class Member>
class Extractor : public std::unary_function<const Owner&, const Member&> {
public:

    Extractor(Member Owner::*member) :
        member_(member) {
    }

    const Member& operator()(const Owner& t) const {
        return t.*member_;
    }

private:

    Member Owner::*member_;

};

template <class Owner, class Member>
Extractor<Owner, Member> makeExtractor(Member Owner::*member) {
    return Extractor<Owner, Member>(member);
}

} // namespace utils
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_EXTRACTOR_HPP_ */
