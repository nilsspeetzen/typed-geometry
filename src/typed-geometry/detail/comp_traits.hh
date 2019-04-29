#pragma once

#include "utility.hh"

#include <typed-geometry/types/fwd.hh>

namespace tg
{
namespace detail
{
template <class Obj>
struct comp_size
{
    static inline constexpr int value = -1;
};
template <int N, class T>
struct comp_size<T const (&)[N]>
{
    static inline constexpr int value = N;
};
template <int D, class T>
struct comp_size<vec<D, T>>
{
    static inline constexpr int value = D;
};
template <int D, class T>
struct comp_size<dir<D, T>>
{
    static inline constexpr int value = D;
};
template <int D, class T>
struct comp_size<pos<D, T>>
{
    static inline constexpr int value = D;
};
template <int D, class T>
struct comp_size<size<D, T>>
{
    static inline constexpr int value = D;
};
template <int D, class T>
struct comp_size<comp<D, T>>
{
    static inline constexpr int value = D;
};

template <class Obj, class ScalarT>
auto test_comp_convertible(int) -> decltype(ScalarT(declval<Obj>()[0]), true_type{});
template <class Obj, class ScalarT>
auto test_comp_convertible(...) -> false_type;

template <class Obj, class = enable_if<comp_size<Obj>::value != -1>>
constexpr int impl_get_dynamic_comp_size(Obj const&, priority_tag<1>)
{
    return comp_size<Obj>::value;
}
template <class Obj>
constexpr auto impl_get_dynamic_comp_size(Obj const& v, priority_tag<0>) -> decltype(int(v.size()))
{
    return int(v.size());
}

template <class Obj>
constexpr int get_dynamic_comp_size(Obj const& v)
{
    return impl_get_dynamic_comp_size(v, priority_tag<1>{});
}
}

template <class Obj, class ScalarT>
constexpr bool is_comp_convertible = decltype(detail::test_comp_convertible<Obj, ScalarT>(0))::value;

template <class Obj>
constexpr bool is_comp_dynamic_size = detail::comp_size<Obj>::value < 0;

template <class Obj, int D, class ScalarT>
constexpr bool is_comp_like = is_comp_convertible<Obj, ScalarT> && (is_comp_dynamic_size<Obj> || detail::comp_size<Obj>::value >= D);
}