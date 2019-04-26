#pragma once

#include "../pos.hh"
#include "../scalar.hh"
#include "../dir.hh"

// An unoriented hyperplane has a distance to the origin and a normal direction
// In dimension n, the distance is 1-dimensional and the normal direction is n-dimensional

// Note that there is a semantic difference between hyperplane and halfspace in nD:
//  - the hyperplane describes all points lying on an (n-1)-dimensional plane
//  - the halfspace describes all points lying inside this n-dimensional subspace
namespace tg
{
template <int D, class ScalarT>
struct hyperplane;

// Common hyperplane types

using hyperplane1 = hyperplane<1, f32>;
using hyperplane2 = hyperplane<2, f32>;
using hyperplane3 = hyperplane<3, f32>;
using hyperplane4 = hyperplane<4, f32>;

using fhyperplane1 = hyperplane<1, f32>;
using fhyperplane2 = hyperplane<2, f32>;
using fhyperplane3 = hyperplane<3, f32>;
using fhyperplane4 = hyperplane<4, f32>;

using dhyperplane1 = hyperplane<1, f64>;
using dhyperplane2 = hyperplane<2, f64>;
using dhyperplane3 = hyperplane<3, f64>;
using dhyperplane4 = hyperplane<4, f64>;

using ihyperplane1 = hyperplane<1, i32>;
using ihyperplane2 = hyperplane<2, i32>;
using ihyperplane3 = hyperplane<3, i32>;
using ihyperplane4 = hyperplane<4, i32>;

using uhyperplane1 = hyperplane<1, u32>;
using uhyperplane2 = hyperplane<2, u32>;
using uhyperplane3 = hyperplane<3, u32>;
using uhyperplane4 = hyperplane<4, u32>;


// ======== IMPLEMENTATION ========

template <int D, class ScalarT>
struct hyperplane
{
    using dis_t = ScalarT;
    using dir_t = dir<D, ScalarT>;
    using pos_t = pos<D, ScalarT>;

    dir_t normal;
    dis_t dis;

    constexpr hyperplane() = default;
    constexpr hyperplane(dir_t n, dis_t d) : normal(n), dis(d) {}
    constexpr hyperplane(dir_t n, pos_t p);
};
} // namespace tg