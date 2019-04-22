#pragma once

#include "../pos.hh"
#include "../scalar.hh"
#include "../size.hh"
#include "../dir.hh"

// A line has a direction and a point lying on it
// The direction is assumed to be normalized
namespace tg
{
template <int D, class ScalarT>
struct line;

// Common line types

using line1 = line<1, f32>;
using line2 = line<2, f32>;
using line3 = line<3, f32>;
using line4 = line<4, f32>;

using fline1 = line<1, f32>;
using fline2 = line<2, f32>;
using fline3 = line<3, f32>;
using fline4 = line<4, f32>;

using dline1 = line<1, f64>;
using dline2 = line<2, f64>;
using dline3 = line<3, f64>;
using dline4 = line<4, f64>;

using iline1 = line<1, i32>;
using iline2 = line<2, i32>;
using iline3 = line<3, i32>;
using iline4 = line<4, i32>;

using uline1 = line<1, u32>;
using uline2 = line<2, u32>;
using uline3 = line<3, u32>;
using uline4 = line<4, u32>;


// ======== IMPLEMENTATION ========

template <int D, class ScalarT>
struct line
{
    using dir_t = dir<D, ScalarT>;
    using pos_t = pos<D, ScalarT>;

    pos_t p;
    dir_t dir;

    constexpr line() = default;
    constexpr line(pos_t p, dir_t dir) : p(p), dir(dir) {}

    // create a line from two points
    static constexpr line from_points(pos_t a, pos_t b)
    {
        return line(a, normalize(b - a));
    }
};
} // namespace tg
