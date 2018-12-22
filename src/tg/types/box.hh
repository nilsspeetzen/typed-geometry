#pragma once

#include "pos.hh"
#include "scalar.hh"
#include "size.hh"
#include "vec.hh"

namespace tg
{
template <int D, class ScalarT>
struct box;

// Common box types

using box1 = box<1, f32>;
using box2 = box<2, f32>;
using box3 = box<3, f32>;
using box4 = box<4, f32>;

using fbox1 = box<1, f32>;
using fbox2 = box<2, f32>;
using fbox3 = box<3, f32>;
using fbox4 = box<4, f32>;

using dbox1 = box<1, f64>;
using dbox2 = box<2, f64>;
using dbox3 = box<3, f64>;
using dbox4 = box<4, f64>;

using ibox1 = box<1, i32>;
using ibox2 = box<2, i32>;
using ibox3 = box<3, i32>;
using ibox4 = box<4, i32>;

using ubox1 = box<1, u32>;
using ubox2 = box<2, u32>;
using ubox3 = box<3, u32>;
using ubox4 = box<4, u32>;


// ======== IMPLEMENTATION ========

template <int D, class ScalarT>
struct box
{
    using vec_t = vec<D, ScalarT>;
    using pos_t = pos<D, ScalarT>;
    using size_t = size<D, ScalarT>;

    // TODO: better?
    pos_t center;
    size_t half_extent;

    constexpr pos_t min() const { return center - half_extent; }
    constexpr pos_t max() const { return center + half_extent; }

    constexpr box() = default;
    constexpr box(pos_t center, size_t half_extent) : center(center), half_extent(half_extent) {}
};
} // namespace tg