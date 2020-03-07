#pragma once

// This file was generated by generate_fixed_uint_multiplications.cc in TGSamples.

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#include <cstring>
#endif

#include <typed-geometry/feature/fixed_int.hh>

namespace tg::detail
{
template <>
inline i128 imul(i64 lhs, i64 rhs)
{
#ifdef _MSC_VER
    return imul(i128(lhs), i128(rhs));
#else
    __int128 l = lhs;
    __int128 r = rhs;
    __int128 inres = l * r;
    i128 res;
    memcpy(&res, &inres, sizeof(__int128));
    return res;
#endif
}

template <>
inline i128 imul(i128 lhs, i64 rhs)
{
#ifdef _MSC_VER
    return imul(lhs, i128(rhs));
#else
    __int128 l;
    __int128 r = rhs;
    memcpy(&l, &lhs, sizeof(__int128));
    __int128 inres = l * r;
    i128 res;
    memcpy(&res, &inres, sizeof(__int128));
    return res;
#endif
}

template <>
inline i128 imul(i64 lhs, i128 rhs)
{
#ifdef _MSC_VER
    return imul(i128(lhs), rhs);
#else
    __int128 l = lhs;
    __int128 r;
    memcpy(&r, &rhs, sizeof(__int128));
    __int128 inres = l * r;
    i128 res;
    memcpy(&res, &inres, sizeof(__int128));
    return res;
#endif
}

template <>
inline i128 imul(i128 lhs, i128 rhs)
{
    i128 res;
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l10 = 0;
    u64 h00 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = u64(lhs.d[0]) * u64(rhs.d[1]);
    l10 = u64(lhs.d[1]) * u64(rhs.d[0]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    res.d[1] = c + h00 + l01 + l10;
    return res;
}

template <>
inline i192 imul(i128 lhs, i64 rhs)
{
    i192 res;
    u64 s_l = u64(i64(lhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
    }
    { // conditional inversion
        rhs = i64((u64(rhs) ^ s_r) - s_r);
    }
    u64 l00 = 0;
    u64 l10 = 0;
    u64 h00 = 0;
    u64 h10 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs), &h00);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs), &h10);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    res.d[2] = c + h10;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
    }
    return res;
}

template <>
inline i192 imul(i192 lhs, i64 rhs)
{
    i192 res;
    u64 s_l = u64(i64(lhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
    }
    { // conditional inversion
        rhs = i64((u64(rhs) ^ s_r) - s_r);
    }
    u64 l00 = 0;
    u64 l10 = 0;
    u64 l20 = 0;
    u64 h00 = 0;
    u64 h10 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs), &h00);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs), &h10);
    l20 = u64(lhs.d[2]) * u64(rhs);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    res.d[2] = c + h10 + l20;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
    }
    return res;
}

template <>
inline i192 imul(i64 lhs, i128 rhs)
{
    i192 res;
    u64 s_l = u64(i64(lhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs = i64((u64(lhs) ^ s_l) - s_l);
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    l00 = _mulx_u64(u64(lhs), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs), u64(rhs.d[1]), &h01);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    res.d[2] = c + h01;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
    }
    return res;
}

template <>
inline i192 imul(i128 lhs, i128 rhs)
{
    i192 res;
    u64 s_l = u64(i64(lhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h10 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = u64(lhs.d[1]) * u64(rhs.d[1]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    res.d[2] = c + h01 + h10 + l11;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
    }
    return res;
}

template <>
inline i192 imul(i192 lhs, i128 rhs)
{
    i192 res;
    u64 s_l = u64(i64(lhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l20 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h10 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = u64(lhs.d[1]) * u64(rhs.d[1]);
    l20 = u64(lhs.d[2]) * u64(rhs.d[0]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    res.d[2] = c + h01 + h10 + l11 + l20;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
    }
    return res;
}

template <>
inline i192 imul(i64 lhs, i192 rhs)
{
    i192 res;
    u64 s_l = u64(i64(lhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs = i64((u64(lhs) ^ s_l) - s_l);
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    l00 = _mulx_u64(u64(lhs), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs), u64(rhs.d[1]), &h01);
    l02 = u64(lhs) * u64(rhs.d[2]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    res.d[2] = c + h01 + l02;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
    }
    return res;
}

template <>
inline i192 imul(i128 lhs, i192 rhs)
{
    i192 res;
    u64 s_l = u64(i64(lhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h10 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l02 = u64(lhs.d[0]) * u64(rhs.d[2]);
    l11 = u64(lhs.d[1]) * u64(rhs.d[1]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    res.d[2] = c + h01 + l02 + h10 + l11;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
    }
    return res;
}

template <>
inline i192 imul(i192 lhs, i192 rhs)
{
    i192 res;
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l20 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h10 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l02 = u64(lhs.d[0]) * u64(rhs.d[2]);
    l11 = u64(lhs.d[1]) * u64(rhs.d[1]);
    l20 = u64(lhs.d[2]) * u64(rhs.d[0]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    res.d[2] = c + h01 + l02 + h10 + l11 + l20;
    return res;
}

template <>
inline i256 imul(i192 lhs, i64 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
    }
    { // conditional inversion
        rhs = i64((u64(rhs) ^ s_r) - s_r);
    }
    u64 l00 = 0;
    u64 l10 = 0;
    u64 l20 = 0;
    u64 h00 = 0;
    u64 h10 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs), &h00);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs), &h10);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs), &h20);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h20;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i256 lhs, i64 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[3]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
        u64 c2 = (lhs.d[2] == 0) & s_l & c1;
        lhs.d[3] = (u64(lhs.d[3]) ^ s_l) + c2;
    }
    { // conditional inversion
        rhs = i64((u64(rhs) ^ s_r) - s_r);
    }
    u64 l00 = 0;
    u64 l10 = 0;
    u64 l20 = 0;
    u64 l30 = 0;
    u64 h00 = 0;
    u64 h10 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs), &h00);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs), &h10);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs), &h20);
    l30 = u64(lhs.d[3]) * u64(rhs);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h20 + l30;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i128 lhs, i128 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    res.d[3] = c + h11;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i192 lhs, i128 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l20 = 0;
    u64 l21 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs.d[0]), &h20);
    l21 = u64(lhs.d[2]) * u64(rhs.d[1]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h11 + h20 + l21;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i256 lhs, i128 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[3]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
        u64 c2 = (lhs.d[2] == 0) & s_l & c1;
        lhs.d[3] = (u64(lhs.d[3]) ^ s_l) + c2;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l20 = 0;
    u64 l21 = 0;
    u64 l30 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs.d[0]), &h20);
    l21 = u64(lhs.d[2]) * u64(rhs.d[1]);
    l30 = u64(lhs.d[3]) * u64(rhs.d[0]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h11 + h20 + l21 + l30;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i64 lhs, i192 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs = i64((u64(lhs) ^ s_l) - s_l);
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    l00 = _mulx_u64(u64(lhs), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs), u64(rhs.d[2]), &h02);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    res.d[3] = c + h02;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i128 lhs, i192 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l12 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[2]), &h02);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l12 = u64(lhs.d[1]) * u64(rhs.d[2]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    res.d[3] = c + h02 + h11 + l12;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i192 lhs, i192 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l12 = 0;
    u64 l20 = 0;
    u64 l21 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[2]), &h02);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs.d[0]), &h20);
    l12 = u64(lhs.d[1]) * u64(rhs.d[2]);
    l21 = u64(lhs.d[2]) * u64(rhs.d[1]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h02 + h11 + l12 + h20 + l21;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i256 lhs, i192 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[3]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
        u64 c2 = (lhs.d[2] == 0) & s_l & c1;
        lhs.d[3] = (u64(lhs.d[3]) ^ s_l) + c2;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l12 = 0;
    u64 l20 = 0;
    u64 l21 = 0;
    u64 l30 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[2]), &h02);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs.d[0]), &h20);
    l12 = u64(lhs.d[1]) * u64(rhs.d[2]);
    l21 = u64(lhs.d[2]) * u64(rhs.d[1]);
    l30 = u64(lhs.d[3]) * u64(rhs.d[0]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h02 + h11 + l12 + h20 + l21 + l30;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i64 lhs, i256 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[3]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs = i64((u64(lhs) ^ s_l) - s_l);
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
        u64 c2 = (rhs.d[2] == 0) & s_r & c1;
        rhs.d[3] = (u64(rhs.d[3]) ^ s_r) + c2;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l03 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    l00 = _mulx_u64(u64(lhs), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs), u64(rhs.d[2]), &h02);
    l03 = u64(lhs) * u64(rhs.d[3]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    res.d[3] = c + h02 + l03;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i128 lhs, i256 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[1]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[3]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
        u64 c2 = (rhs.d[2] == 0) & s_r & c1;
        rhs.d[3] = (u64(rhs.d[3]) ^ s_r) + c2;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l03 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l12 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[2]), &h02);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l03 = u64(lhs.d[0]) * u64(rhs.d[3]);
    l12 = u64(lhs.d[1]) * u64(rhs.d[2]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    res.d[3] = c + h02 + l03 + h11 + l12;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i192 lhs, i256 rhs)
{
    i256 res;
    u64 s_l = u64(i64(lhs.d[2]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_r = u64(i64(rhs.d[3]) >> 63); // 0 iff > 0, -1 otherwise
    u64 s_res = s_l ^ s_r;
    { // conditional inversion
        lhs.d[0] = ((u64(lhs.d[0]) ^ s_l) - s_l);
        u64 c0 = (lhs.d[0] == 0) & s_l;
        lhs.d[1] = (u64(lhs.d[1]) ^ s_l) + c0;
        u64 c1 = (lhs.d[1] == 0) & s_l & c0;
        lhs.d[2] = (u64(lhs.d[2]) ^ s_l) + c1;
    }
    { // conditional inversion
        rhs.d[0] = ((u64(rhs.d[0]) ^ s_r) - s_r);
        u64 c0 = (rhs.d[0] == 0) & s_r;
        rhs.d[1] = (u64(rhs.d[1]) ^ s_r) + c0;
        u64 c1 = (rhs.d[1] == 0) & s_r & c0;
        rhs.d[2] = (u64(rhs.d[2]) ^ s_r) + c1;
        u64 c2 = (rhs.d[2] == 0) & s_r & c1;
        rhs.d[3] = (u64(rhs.d[3]) ^ s_r) + c2;
    }
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l03 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l12 = 0;
    u64 l20 = 0;
    u64 l21 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[2]), &h02);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs.d[0]), &h20);
    l03 = u64(lhs.d[0]) * u64(rhs.d[3]);
    l12 = u64(lhs.d[1]) * u64(rhs.d[2]);
    l21 = u64(lhs.d[2]) * u64(rhs.d[1]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h02 + l03 + h11 + l12 + h20 + l21;
    { // conditional inversion
        res.d[0] = ((u64(res.d[0]) ^ s_res) - s_res);
        u64 c0 = (res.d[0] == 0) & s_res;
        res.d[1] = (u64(res.d[1]) ^ s_res) + c0;
        u64 c1 = (res.d[1] == 0) & s_res & c0;
        res.d[2] = (u64(res.d[2]) ^ s_res) + c1;
        u64 c2 = (res.d[2] == 0) & s_res & c1;
        res.d[3] = (u64(res.d[3]) ^ s_res) + c2;
    }
    return res;
}

template <>
inline i256 imul(i256 lhs, i256 rhs)
{
    i256 res;
    u64 l00 = 0;
    u64 l01 = 0;
    u64 l02 = 0;
    u64 l03 = 0;
    u64 l10 = 0;
    u64 l11 = 0;
    u64 l12 = 0;
    u64 l20 = 0;
    u64 l21 = 0;
    u64 l30 = 0;
    u64 h00 = 0;
    u64 h01 = 0;
    u64 h02 = 0;
    u64 h10 = 0;
    u64 h11 = 0;
    u64 h20 = 0;
    l00 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[0]), &h00);
    l01 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[1]), &h01);
    l02 = _mulx_u64(u64(lhs.d[0]), u64(rhs.d[2]), &h02);
    l10 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[0]), &h10);
    l11 = _mulx_u64(u64(lhs.d[1]), u64(rhs.d[1]), &h11);
    l20 = _mulx_u64(u64(lhs.d[2]), u64(rhs.d[0]), &h20);
    l03 = u64(lhs.d[0]) * u64(rhs.d[3]);
    l12 = u64(lhs.d[1]) * u64(rhs.d[2]);
    l21 = u64(lhs.d[2]) * u64(rhs.d[1]);
    l30 = u64(lhs.d[3]) * u64(rhs.d[0]);
    unsigned char c = 0;
    c += _addcarry_u64(0, res.d[0], l00, &res.d[0]);
    c += _addcarry_u64(0, res.d[1], c, &res.d[1]);
    c = 0;
    c += _addcarry_u64(0, res.d[1], h00, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l01, &res.d[1]);
    c += _addcarry_u64(0, res.d[1], l10, &res.d[1]);
    c += _addcarry_u64(0, res.d[2], c, &res.d[2]);
    c = 0;
    c += _addcarry_u64(0, res.d[2], h01, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l02, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], h10, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l11, &res.d[2]);
    c += _addcarry_u64(0, res.d[2], l20, &res.d[2]);
    res.d[3] = c + h02 + l03 + h11 + l12 + h20 + l21 + l30;
    return res;
}

} // namespace tg::detail