#pragma once

#include <typed-geometry/detail/scalar_traits.hh>
#include <typed-geometry/types/dir.hh>
#include <typed-geometry/types/vec.hh>

namespace tg
{
template <class ScalarT>
TG_NODISCARD constexpr vec<3, squared_result<ScalarT>> cross(vec<3, ScalarT> const& a, vec<3, ScalarT> const& b)
{
    return {
        a.y * squared_result<ScalarT>(b.z) - a.z * squared_result<ScalarT>(b.y), //
        a.z * squared_result<ScalarT>(b.x) - a.x * squared_result<ScalarT>(b.z), //
        a.x * squared_result<ScalarT>(b.y) - a.y * squared_result<ScalarT>(b.x)  //
    };
}

template <class ScalarT>
TG_NODISCARD constexpr squared_result<ScalarT> cross(vec<2, ScalarT> const& a, vec<2, ScalarT> const& b)
{
    return a.x * squared_result<ScalarT>(b.y) - a.y * squared_result<ScalarT>(b.x);
}

template <class ScalarT>
TG_NODISCARD constexpr vec<3, ScalarT> cross(dir<3, ScalarT> const& a, dir<3, ScalarT> const& b)
{
    return {
        a.y * b.z - a.z * b.y, //
        a.z * b.x - a.x * b.z, //
        a.x * b.y - a.y * b.x  //
    };
}

template <class ScalarT>
TG_NODISCARD constexpr ScalarT cross(dir<2, ScalarT> const& a, dir<2, ScalarT> const& b)
{
    return a.x * b.y - a.y * b.x;
}

} // namespace tg