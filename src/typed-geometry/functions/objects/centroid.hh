#pragma once

#include <typed-geometry/detail/scalar_traits.hh>
#include <typed-geometry/detail/special_values.hh>
#include <typed-geometry/types/objects/aabb.hh>
#include <typed-geometry/types/objects/capsule.hh>
#include <typed-geometry/types/objects/cylinder.hh>
#include <typed-geometry/types/objects/segment.hh>
#include <typed-geometry/types/objects/sphere.hh>
#include <typed-geometry/types/objects/triangle.hh>

#include <typed-geometry/detail/operators/ops_pos.hh>
#include <typed-geometry/detail/operators/ops_vec.hh>

#include <typed-geometry/functions/basic/mix.hh>

// returns the arithmetic mean of all points contained in an object
// has variadic versions

namespace tg
{
template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, ScalarT> centroid(pos<D, ScalarT> const& p)
{
    return p;
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, ScalarT> centroid(pos<D, ScalarT> const& a, pos<D, ScalarT> const& b)
{
    return mix(a, b, ScalarT(0.5));
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, ScalarT> centroid(box<D, ScalarT> const& b)
{
    return b.center;
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, fractional_result<ScalarT>> centroid(aabb<D, ScalarT> const& p)
{
    return mix(p.min, p.max, ScalarT(0.5));
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, fractional_result<ScalarT>> centroid(triangle<D, ScalarT> const& p)
{
    auto z = tg::zero<pos<D, ScalarT>>();
    return z + ((p.pos0 - z) + (p.pos1 - z) + (p.pos2 - z)) / ScalarT(3);
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, fractional_result<ScalarT>> centroid(segment<D, ScalarT> const& p)
{
    return mix(p.pos0, p.pos1, fractional_result<ScalarT>(0.5));
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, ScalarT> centroid(sphere<D, ScalarT> const& p)
{
    return p.center;
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, fractional_result<ScalarT>> centroid(cylinder<D, ScalarT> const& c)
{
    return centroid(c.axis);
}

template <int D, class ScalarT>
[[nodiscard]] constexpr pos<D, fractional_result<ScalarT>> centroid(capsule<D, ScalarT> const& c)
{
    return centroid(c.axis);
}
} // namespace tg