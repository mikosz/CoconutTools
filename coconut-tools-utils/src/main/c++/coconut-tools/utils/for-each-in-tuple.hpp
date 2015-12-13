#ifndef COCONUT_TOOLS_UTILS_FOR_EACH_IN_TUPLE_HPP_
#define COCONUT_TOOLS_UTILS_FOR_EACH_IN_TUPLE_HPP_

#include <tuple>

namespace coconut_tools {
namespace utils {

namespace detail {

template <size_t... Is>
struct Seq {
};

template <size_t N, size_t... Is>
struct GenSeq : GenSeq<N - 1, N - 1, Is...> {
};

template <size_t... Is>
struct GenSeq<0, Is...> : Seq<Is...> {
};

template <class T, class F, int... Is>
void forEachInTuple(T&& t, F f, Seq<Is...>) {
	auto l = { (f(std::get<Is>(t)), 0)... };
}

} // namespace detail

template <class... Ts, class F>
void forEachInTuple(const std::tuple<Ts...>& t, F f) {
	detail::forEachInTuple(t, f, detail::GenSeq<sizeof...(Ts)>());
}

} // namespace utils
} // namespace coconut_tools

#endif /* COCONUT_TOOLS_UTILS_FOR_EACH_IN_TUPLE_HPP_ */
