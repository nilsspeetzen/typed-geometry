#pragma once

#include <initializer_list>

#include <typed-geometry/detail/scalar_traits.hh>

#include <typed-geometry/types/color.hh>
#include <typed-geometry/types/pos.hh>
#include <typed-geometry/types/range.hh>
#include <typed-geometry/types/scalars/scalars.hh>

#include <typed-geometry/types/objects/aabb.hh>
#include <typed-geometry/types/objects/box.hh>
#include <typed-geometry/types/objects/capsule.hh>
#include <typed-geometry/types/objects/cone.hh>
#include <typed-geometry/types/objects/cylinder.hh>
#include <typed-geometry/types/objects/hemisphere.hh>
#include <typed-geometry/types/objects/sphere.hh>
#include <typed-geometry/types/objects/triangle.hh>

#include <typed-geometry/functions/basic/minmax.hh>
#include <typed-geometry/functions/basic/mix.hh>
#include <typed-geometry/functions/vector/math.hh>

#include "random.hh"

/*
 * uniform(rng)       - fair coin flip
 * uniform(rng, a, b) - uniform between a..b (inclusive!)
 * uniform(rng, obj)  - uniform sample from obj
 *
 * Note:
 *  to "uniformly sample" vec3(0)..vec3(1) independent per component, use uniform(rng, tg::aabb3(0, 1))
 *  to "uniformly sample" vec3(0)..vec3(1) as a segment, use uniform(rng, tg::segment3({0,0,0}, {1,1,1}))
 *
 * uniform_vec(rng, ...) same as uniform but returns uniform(rng, ...) as a vector
 */

// TODO: uniform int/uint distribution might need some improvement but is currently faster than the stdlib versions

namespace tg
{
namespace detail
{
template <class T>
struct sampler
{
    static_assert(sizeof(T) >= 0, "sampling of this type not supported without parameters");
};
}

template <class T, class Rng>
[[nodiscard]] constexpr T uniform(Rng& rng)
{
    return detail::sampler<T>::uniform(rng);
}

template <class Rng>
[[nodiscard]] constexpr f32 uniform(Rng& rng, f32 a, f32 b)
{
    return mix(a, b, detail::uniform01<f32>(rng));
}
template <class Rng>
[[nodiscard]] constexpr f64 uniform(Rng& rng, f64 a, f64 b)
{
    return mix(a, b, detail::uniform01<f64>(rng));
}
template <class Rng>
[[nodiscard]] constexpr i32 uniform(Rng& rng, i32 a, i32 b_inc)
{
    TG_CONTRACT(a <= b_inc);
    i32 r = 0;
    auto fa = f32(a);
    auto fb = f32(b_inc) + 1;
    do
    {
        r = tg::ifloor(uniform(rng, fa, fb));
    } while (r > b_inc);
    return r;
}
template <class Rng>
[[nodiscard]] constexpr long uniform(Rng& rng, long a, long b_inc)
{
    TG_CONTRACT(a <= b_inc);
    long r = 0;
    auto fa = f64(a);
    auto fb = f64(b_inc) + 1;
    do
    {
        r = (long)tg::ifloor(uniform(rng, fa, fb));
    } while (r > b_inc);
    return r;
}
template <class Rng>
[[nodiscard]] constexpr i64 uniform(Rng& rng, long long a, long long b_inc)
{
    TG_CONTRACT(a <= b_inc);
    long long r = 0;
    auto fa = f64(a);
    auto fb = f64(b_inc) + 1;
    do
    {
        r = (long long)tg::ifloor(uniform(rng, fa, fb));
    } while (r > b_inc);
    return r;
}
template <class Rng>
[[nodiscard]] constexpr u32 uniform(Rng& rng, u32 a, u32 b_inc)
{
    u32 r = 0;
    auto fa = f32(a);
    auto fb = f32(b_inc) + 1;
    do
    {
        r = u32(tg::ifloor(uniform(rng, fa, fb)));
    } while (r > b_inc);
    return r;
}
template <class Rng>
[[nodiscard]] constexpr unsigned long uniform(Rng& rng, unsigned long a, unsigned long b_inc)
{
    TG_CONTRACT(a <= b_inc);
    unsigned long r = 0;
    auto fa = f64(a);
    auto fb = f64(b_inc) + 1;
    do
    {
        r = (unsigned long)(tg::ifloor(uniform(rng, fa, fb)));
    } while (r > b_inc);
    return r;
}
template <class Rng>
[[nodiscard]] constexpr unsigned long long uniform(Rng& rng, unsigned long long a, unsigned long long b_inc)
{
    TG_CONTRACT(a <= b_inc);
    unsigned long long r = 0;
    auto fa = f64(a);
    auto fb = f64(b_inc) + 1;
    do
    {
        r = (unsigned long long)(tg::ifloor(uniform(rng, fa, fb)));
    } while (r > b_inc);
    return r;
}
template <class Rng>
[[nodiscard]] constexpr char uniform(Rng& rng, char a, char b_inc)
{
    return char(uniform(rng, i32(a), i32(b_inc)));
}
template <class Rng>
[[nodiscard]] constexpr i8 uniform(Rng& rng, i8 a, i8 b_inc)
{
    return i8(uniform(rng, i32(a), i32(b_inc)));
}
template <class Rng>
[[nodiscard]] constexpr i16 uniform(Rng& rng, i16 a, i16 b_inc)
{
    return i16(uniform(rng, i32(a), i32(b_inc)));
}
template <class Rng>
[[nodiscard]] constexpr u8 uniform(Rng& rng, u8 a, u8 b_inc)
{
    return u8(uniform(rng, i32(a), i32(b_inc)));
}
template <class Rng>
[[nodiscard]] constexpr u16 uniform(Rng& rng, u16 a, u16 b_inc)
{
    return u16(uniform(rng, i32(a), i32(b_inc)));
}

template <class T, class Rng>
[[nodiscard]] constexpr angle_t<T> uniform(Rng& rng, angle_t<T> a, angle_t<T> b)
{
    return mix(a, b, detail::uniform01<T>(rng));
}

template <class Rng, class T>
[[nodiscard]] constexpr T uniform(Rng& rng, std::initializer_list<T> list)
{
    TG_CONTRACT(list.size() > 0 && "cannot pick from an empty list");
    return list.begin()[uniform(rng, u64(0), u64(list.size() - 1))];
}

template <class Rng, class Container>
[[nodiscard]] constexpr auto uniform(Rng& rng, Container& c) -> decltype(c[c.size()])
{
    TG_CONTRACT(c.size() > 0 && "cannot pick from an empty container");
    return c[uniform(rng, u64(0), u64(c.size() - 1))];
}

template <class Rng>
[[nodiscard]] constexpr int uniform(Rng& rng, range1 const& b)
{
    return uniform(rng, b.min, b.max - 1);
}

template <class Rng>
[[nodiscard]] constexpr comp<2, int> uniform(Rng& rng, range2 const& b)
{
    return {uniform(rng, b.min.comp0, b.max.comp0 - 1), //
            uniform(rng, b.min.comp1, b.max.comp1 - 1)};
}

template <class Rng>
[[nodiscard]] constexpr comp<3, int> uniform(Rng& rng, range3 const& b)
{
    return {uniform(rng, b.min.comp0, b.max.comp0 - 1), //
            uniform(rng, b.min.comp1, b.max.comp1 - 1), //
            uniform(rng, b.min.comp2, b.max.comp2 - 1)};
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<1, ScalarT> uniform(Rng& rng, aabb<1, ScalarT> const& b)
{
    return {uniform(rng, b.min.x, b.max.x)};
}
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<2, ScalarT> uniform(Rng& rng, aabb<2, ScalarT> const& b)
{
    return {uniform(rng, b.min.x, b.max.x), //
            uniform(rng, b.min.y, b.max.y)};
}
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, aabb<3, ScalarT> const& b)
{
    return {uniform(rng, b.min.x, b.max.x), //
            uniform(rng, b.min.y, b.max.y), //
            uniform(rng, b.min.z, b.max.z)};
}
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<4, ScalarT> uniform(Rng& rng, aabb<4, ScalarT> const& b)
{
    return {uniform(rng, b.min.x, b.max.x), //
            uniform(rng, b.min.y, b.max.y), //
            uniform(rng, b.min.z, b.max.z), //
            uniform(rng, b.min.w, b.max.w)};
}
// uniform_boundary(aabb1) == uniform(aabb1)
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<2, ScalarT> uniform(Rng& rng, aabb_boundary<2, ScalarT> const& b)
{
    auto extends = b.max - b.min;
    if (uniform(rng, ScalarT(0), extends.x + extends.y) < extends.x)
        return {uniform(rng, b.min.x, b.max.x), //
                uniform(rng) ? b.min.y : b.max.y};

    return {uniform(rng) ? b.min.x : b.max.x, //
            uniform(rng, b.min.y, b.max.y)};
}
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, aabb_boundary<3, ScalarT> const& b)
{
    auto extends = b.max - b.min;
    auto areaX = extends.y * extends.z;
    auto areaY = extends.x * extends.z;
    auto areaZ = extends.x * extends.y;

    auto res = uniform(rng, b); // Sample a random point inside the aabb
    // Project to one of the sides, proportional to their area
    auto part = uniform(rng, ScalarT(0), areaX + areaY + areaZ);
    int i = part < areaX ? 0 : part < areaX + areaY ? 1 : 2;
    res[i] = uniform<bool>(rng) ? b.min[i] : b.max[i];
    return res;
}
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<4, ScalarT> uniform(Rng& rng, aabb_boundary<4, ScalarT> const& b)
{
    auto extends = b.max - b.min;
    auto volX = extends.y * extends.z * extends.w;
    auto volY = extends.x * extends.z * extends.w;
    auto volZ = extends.x * extends.y * extends.w;
    auto volW = extends.x * extends.y * extends.z;

    auto res = uniform(rng, b); // Sample a random point inside the aabb
    // Project to one of the borders, proportional to their volume
    auto part = uniform(rng, ScalarT(0), volX + volY + volZ + volW);
    int i = part < volX + volY ? (part < volX ? 0 : 1) : (part < volX + volY + volZ ? 2 : 3);
    res[i] = uniform<bool>(rng) ? b.min[i] : b.max[i];
    return res;
}

template <int D, class ScalarT, class Rng>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, segment<D, ScalarT> const& s)
{
    return mix(s.pos0, s.pos1, detail::uniform01<ScalarT>(rng));
}

template <int D, class ScalarT, class Rng>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, box<D, ScalarT> const& b)
{
    return b.center + b.half_extents * uniform_vec(rng, aabb<D, ScalarT>::minus_one_to_one);
}
template <int D, class ScalarT, class Rng>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, box_boundary<D, ScalarT> const& b)
{
    return b.center + b.half_extents * (uniform(rng, aabb_boundary<D, ScalarT>::minus_one_to_one) - pos<D, ScalarT>::zero);
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<2, ScalarT> uniform(Rng& rng, sphere_boundary<2, ScalarT> const& c)
{
    return c.center + c.radius * uniform<dir<2, ScalarT>>(rng);
}
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, sphere_boundary<2, ScalarT, 3> const& c)
{
    auto direction = uniform<dir<2, ScalarT>>(rng);
    auto x = any_normal(c.normal);
    auto y = cross(c.normal, x);
    return c.center + c.radius * (direction.x * x + direction.y * y);
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, sphere<2, ScalarT, 3> const& d)
{
    auto direction = uniform(rng, sphere<2, ScalarT>(pos<2, ScalarT>::zero, d.radius));
    auto x = any_normal(d.normal);
    auto y = cross(d.normal, x);
    return d.center + direction.x * x + direction.y * y;
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, cylinder<3, ScalarT> const& t)
{
    auto d = sphere<2, ScalarT, 3>(pos<3, ScalarT>::zero, t.radius, normalize(t.axis.pos1 - t.axis.pos0));
    return uniform(rng, t.axis) + vec<3, ScalarT>(uniform(rng, d));
}
template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, cylinder_boundary_no_caps<3, ScalarT> const& t)
{
    auto c = sphere_boundary<3, ScalarT>(pos<3, ScalarT>::zero, t.radius, normalize(t.axis.pos1 - t.axis.pos0));
    return uniform(rng, t.axis) + vec<3, ScalarT>(uniform(rng, c));
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, cylinder_boundary<3, ScalarT> const& c)
{
    auto x = c.axis.pos1 - c.axis.pos0;
    auto h = length(x);
    auto sideArea = ScalarT(2) * c.radius * h; // * Pi, but that does not matter here
    auto capArea = c.radius * c.radius;        // * Pi
    auto totalArea = ScalarT(2) * capArea + sideArea;
    auto part = detail::uniform01<ScalarT>(rng) * totalArea;
    if (part < sideArea) // Uniform sampling on cylinder side
        return uniform(rng, cylinder_boundary_no_caps<3, ScalarT>(c.axis, c.radius));

    // Otherwise sampling on one of the caps
    auto capDisk = sphere<2, ScalarT, 3>(part < sideArea + capArea ? c.axis.pos0 : c.axis.pos1, c.radius, normalize(x));
    return uniform(rng, capDisk);
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, capsule<3, ScalarT> const& c)
{
    auto x = c.axis.pos1 - c.axis.pos0;
    auto h = length(x);
    auto tubeVolume = c.radius * c.radius * h;                                 // * Pi, but that does not matter here
    auto capVolume = ScalarT(2) / ScalarT(3) * c.radius * c.radius * c.radius; // * Pi
    auto totalVolume = ScalarT(2) * capVolume + tubeVolume;
    auto part = detail::uniform01<ScalarT>(rng) * totalVolume;
    if (part < tubeVolume) // Uniform sampling in capsule tube part
        return uniform(rng, cylinder<3, ScalarT>(c.axis, c.radius));

    // Otherwise sampling in one of the caps
    auto capHemi = hemisphere<3, ScalarT>();
    capHemi.radius = c.radius;
    capHemi.center = part < tubeVolume + capVolume ? c.axis.pos0 : c.axis.pos1;
    capHemi.normal = part < tubeVolume + capVolume ? -normalize(x) : normalize(x);
    return uniform(rng, capHemi);
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, capsule_boundary<3, ScalarT> const& c)
{
    auto x = c.axis.pos1 - c.axis.pos0;
    auto h = length(x);
    auto sideArea = ScalarT(2) * c.radius * h; // * Pi, but that does not matter here
    auto capArea = c.radius * c.radius;        // * Pi
    auto totalArea = ScalarT(2) * capArea + sideArea;
    auto part = detail::uniform01<ScalarT>(rng) * totalArea;
    if (part < sideArea) // Uniform sampling on capsule side
        return uniform(rng, cylinder_boundary<3, ScalarT>(c.axis, c.radius));

    // Otherwise sampling on one of the caps
    auto capHemi = hemisphere_boundary<3, ScalarT>();
    capHemi.radius = c.radius;
    capHemi.center = part < sideArea + capArea ? c.axis.pos0 : c.axis.pos1;
    capHemi.normal = part < sideArea + capArea ? -normalize(x) : normalize(x);
    return uniform(rng, capHemi);
}

template <int D, class ScalarT, class Rng>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, sphere_boundary<D, ScalarT> const& s)
{
    auto ub = tg::aabb<D, ScalarT>::minus_one_to_one;
    while (true)
    {
        auto p = uniform_vec(rng, ub);
        auto l = length_sqr(p);
        if (l > ScalarT(0) && l <= ScalarT(1))
            return s.center + p * (s.radius / sqrt(l));
    }
}

template <int D, class ScalarT, class Rng>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, sphere<D, ScalarT> const& b)
{
    auto ub = tg::aabb<D, ScalarT>::minus_one_to_one;
    while (true)
    {
        auto p = uniform_vec(rng, ub);
        auto l = length_sqr(p);
        if (l <= ScalarT(1))
            return b.center + p * b.radius;
    }
}

template <class ScalarT, class Rng>
[[nodiscard]] constexpr pos<3, ScalarT> uniform(Rng& rng, cone_boundary_no_caps<3, ScalarT> const& c) // boundary, no_caps (not on base)
{
    auto ub = tg::aabb<2, ScalarT>::minus_one_to_one;
    while (true)
    {
        auto p = uniform_vec(rng, ub);
        auto l = length_sqr(p);
        if (l <= ScalarT(1))
        {
            p *= c.base.radius;
            auto x = any_normal(c.base.normal);
            auto y = cross(c.base.normal, x);
            return c.base.center + p.x * x + p.y * y + (ScalarT(1) - sqrt(l)) * c.base.normal * c.height;
        }
    }
}

template <int D, class ScalarT, class Rng>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, hemisphere<D, ScalarT> const& h)
{
    auto p = uniform(rng, sphere<D, ScalarT>(h.center, h.radius));
    auto v = p - h.center;
    if (dot(v, h.normal) >= ScalarT(0))
        return p;
    else
        return h.center - v;
}
template <int D, class ScalarT, class Rng>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, hemisphere_boundary_no_caps<D, ScalarT> const& h)
{
    auto p = uniform(rng, sphere<D, ScalarT>(h.center, h.radius));
    auto v = p - h.center;
    if (dot(v, h.normal) >= ScalarT(0))
        return p;
    else
        return h.center - v;
}

template <int D, class ScalarT, class Rng, class = enable_if<is_floating_point<ScalarT>>>
[[deprecated("potentially misleading operation. use uniform_vec(rng, tg::aabb3(..)) or uniform_vec(rng, tg::segment3(..)) depending on your intended "
             "semantics")]] [[nodiscard]] constexpr vec<D, ScalarT>
uniform(Rng& rng, vec<D, ScalarT> const& a, vec<D, ScalarT> const& b)
{
    return mix(a, b, detail::uniform01<ScalarT>(rng));
}
template <int D, class ScalarT, class Rng, class = enable_if<is_floating_point<ScalarT>>>
[[deprecated("potentially misleading operation. use uniform(rng, tg::aabb3(..)) or uniform(rng, tg::segment3(..)) depending on your intended "
             "semantics")]] [[nodiscard]] constexpr pos<D, ScalarT>
uniform(Rng& rng, pos<D, ScalarT> const& a, pos<D, ScalarT> const& b)
{
    return mix(a, b, detail::uniform01<ScalarT>(rng));
}

template <int D, class ScalarT, class Rng, class = enable_if<is_floating_point<ScalarT>>>
[[nodiscard]] constexpr pos<D, ScalarT> uniform(Rng& rng, triangle<D, ScalarT> const& t)
{
    auto e0 = t.pos1 - t.pos0;
    auto e1 = t.pos2 - t.pos0;
    auto u0 = uniform(rng, ScalarT(0), ScalarT(1));
    auto u1 = uniform(rng, ScalarT(0), ScalarT(1));
    if (u0 + u1 > ScalarT(1))
    {
        u0 = ScalarT(1) - u0;
        u1 = ScalarT(1) - u1;
    }
    return t.pos0 + u0 * e0 + u1 * e1;
}

template <class Rng, class... Args>
[[nodiscard]] constexpr auto uniform_vec(Rng& rng, Args const&... args) -> decltype(uniform(rng, args...) - decltype(uniform(rng, args...))::zero)
{
    return uniform(rng, args...) - decltype(uniform(rng, args...))::zero;
}


namespace detail
{
template <>
struct sampler<bool>
{
    template <class Rng>
    constexpr static bool uniform(Rng& rng)
    {
        return rng() & 1;
    }
};
template <class T>
struct sampler<angle_t<T>>
{
    template <class Rng>
    constexpr static angle_t<T> uniform(Rng& rng)
    {
        return tg::uniform(rng, tg::radians(T(0)), 2 * tg::pi<T>);
    }
};
template <class T>
struct sampler<color<3, T>>
{
    template <class Rng>
    constexpr static color<3, T> uniform(Rng& rng)
    {
        return tg::color3(tg::uniform(rng, T(0), T(1)), tg::uniform(rng, T(0), T(1)), tg::uniform(rng, T(0), T(1)));
    }
};
template <class T>
struct sampler<color<4, T>>
{
    template <class Rng>
    constexpr static color<4, T> uniform(Rng& rng)
    {
        return tg::color3(tg::uniform(rng, T(0), T(1)), tg::uniform(rng, T(0), T(1)), tg::uniform(rng, T(0), T(1)), tg::uniform(rng, T(0), T(1)));
    }
};
template <int D, class ScalarT>
struct sampler<dir<D, ScalarT>>
{
    template <class Rng>
    constexpr static dir<D, ScalarT> uniform(Rng& rng)
    {
        auto ub = tg::aabb<D, ScalarT>::minus_one_to_one;
        while (true)
        {
            auto p = uniform_vec(rng, ub);
            auto l = length_sqr(p);
            if (l > ScalarT(0) && l <= ScalarT(1))
                return tg::dir<D, ScalarT>(p / sqrt(l));
        }
    }
};
}

} // namespace tg