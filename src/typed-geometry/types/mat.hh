#pragma once

#include "scalar.hh"
#include "vec.hh"

namespace tg
{
/*
 * Memory layout of a 4x4:
 *  0  4  8 12
 *  1  5  9 13
 *  2  6 10 14
 *  3  7 11 15
 *
 * i.e. col-major
 *
 * matCxR (cols x rows)
 *
 * mat3x4 has no translational part
 * mat4x3 has no projective part
 *
 * mat[i] is i-th column (assignable as vec)
 * mat.col(i), mat.row(i) return i-th column and row, respectively
 *
 * NOTE: default initialization is zero, NOT identity
 *       use tg::identity<mat4>() to get identity matrix
 */
template <int C, int R, class ScalarT>
struct mat;

// square matrices

using mat1 = mat<1, 1, f32>;
using mat2 = mat<2, 2, f32>;
using mat3 = mat<3, 3, f32>;
using mat4 = mat<4, 4, f32>;

using fmat1 = mat<1, 1, f32>;
using fmat2 = mat<2, 2, f32>;
using fmat3 = mat<3, 3, f32>;
using fmat4 = mat<4, 4, f32>;

using dmat1 = mat<1, 1, f64>;
using dmat2 = mat<2, 2, f64>;
using dmat3 = mat<3, 3, f64>;
using dmat4 = mat<4, 4, f64>;

using imat1 = mat<1, 1, i32>;
using imat2 = mat<2, 2, i32>;
using imat3 = mat<3, 3, i32>;
using imat4 = mat<4, 4, i32>;

using umat1 = mat<1, 1, u32>;
using umat2 = mat<2, 2, u32>;
using umat3 = mat<3, 3, u32>;
using umat4 = mat<4, 4, u32>;

// rectangle matrices

using mat2x2 = mat<2, 2, f32>;
using mat2x3 = mat<2, 3, f32>;
using mat2x4 = mat<2, 4, f32>;
using mat3x2 = mat<3, 2, f32>;
using mat3x3 = mat<3, 3, f32>;
using mat3x4 = mat<3, 4, f32>;
using mat4x2 = mat<4, 2, f32>;
using mat4x3 = mat<4, 3, f32>;
using mat4x4 = mat<4, 4, f32>;

using fmat2x2 = mat<2, 2, f32>;
using fmat2x3 = mat<2, 3, f32>;
using fmat2x4 = mat<2, 4, f32>;
using fmat3x2 = mat<3, 2, f32>;
using fmat3x3 = mat<3, 3, f32>;
using fmat3x4 = mat<3, 4, f32>;
using fmat4x2 = mat<4, 2, f32>;
using fmat4x3 = mat<4, 3, f32>;
using fmat4x4 = mat<4, 4, f32>;

using dmat2x2 = mat<2, 2, f64>;
using dmat2x3 = mat<2, 3, f64>;
using dmat2x4 = mat<2, 4, f64>;
using dmat3x2 = mat<3, 2, f64>;
using dmat3x3 = mat<3, 3, f64>;
using dmat3x4 = mat<3, 4, f64>;
using dmat4x2 = mat<4, 2, f64>;
using dmat4x3 = mat<4, 3, f64>;
using dmat4x4 = mat<4, 4, f64>;

using imat2x2 = mat<2, 2, i32>;
using imat2x3 = mat<2, 3, i32>;
using imat2x4 = mat<2, 4, i32>;
using imat3x2 = mat<3, 2, i32>;
using imat3x3 = mat<3, 3, i32>;
using imat3x4 = mat<3, 4, i32>;
using imat4x2 = mat<4, 2, i32>;
using imat4x3 = mat<4, 3, i32>;
using imat4x4 = mat<4, 4, i32>;

using umat2x2 = mat<2, 2, u32>;
using umat2x3 = mat<2, 3, u32>;
using umat2x4 = mat<2, 4, u32>;
using umat3x2 = mat<3, 2, u32>;
using umat3x3 = mat<3, 3, u32>;
using umat3x4 = mat<3, 4, u32>;
using umat4x2 = mat<4, 2, u32>;
using umat4x3 = mat<4, 3, u32>;
using umat4x4 = mat<4, 4, u32>;


// ======== IMPLEMENTATION ========


namespace detail
{
template <int R, class ScalarT>
constexpr vec<1, ScalarT> mat_row(mat<1, R, ScalarT> const& m, int i)
{
    return {m[0][i]};
}
template <int R, class ScalarT>
constexpr vec<2, ScalarT> mat_row(mat<2, R, ScalarT> const& m, int i)
{
    return {m[0][i], m[1][i]};
}
template <int R, class ScalarT>
constexpr vec<3, ScalarT> mat_row(mat<3, R, ScalarT> const& m, int i)
{
    return {m[0][i], m[1][i], m[2][i]};
}
template <int R, class ScalarT>
constexpr vec<4, ScalarT> mat_row(mat<4, R, ScalarT> const& m, int i)
{
    return {m[0][i], m[1][i], m[2][i], m[3][i]};
}
} // namespace detail

template <int C, int R, class ScalarT>
struct mat
{
    vec<R, ScalarT> m[C];

    constexpr vec<R, ScalarT>& operator[](int i) { return m[i]; }
    constexpr vec<R, ScalarT> const& operator[](int i) const { return m[i]; }

    constexpr vec<R, ScalarT> col(int i) const { return m[i]; }
    constexpr vec<C, ScalarT> row(int i) const { return detail::mat_row(*this, i); }

    static const mat zero;
    static const mat ones;
    static const mat identity;

    static constexpr mat<C, R, ScalarT> diag(ScalarT v);
    static constexpr mat<C, R, ScalarT> diag(vec<detail::min(C, R), ScalarT> const& v);
};

template <int R, class ScalarT>
constexpr bool operator==(mat<1, R, ScalarT> const& a, mat<1, R, ScalarT> const& b)
{
    return a[0] == b[0];
}
template <int R, class ScalarT>
constexpr bool operator==(mat<2, R, ScalarT> const& a, mat<2, R, ScalarT> const& b)
{
    return a[0] == b[0] && a[1] == b[1];
}
template <int R, class ScalarT>
constexpr bool operator==(mat<3, R, ScalarT> const& a, mat<3, R, ScalarT> const& b)
{
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}
template <int R, class ScalarT>
constexpr bool operator==(mat<4, R, ScalarT> const& a, mat<4, R, ScalarT> const& b)
{
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}
template <int C, int R, class ScalarT>
constexpr bool operator!=(mat<C, R, ScalarT> const& a, mat<C, R, ScalarT> const& b)
{
    return !(a == b);
}

} // namespace tg