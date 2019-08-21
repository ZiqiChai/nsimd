/*

Copyright (c) 2019 Agenium Scale

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef NSIMD_MODULES_FIXED_POINT_HPP
#define NSIMD_MODULES_FIXED_POINT_HPP

#include "fixed_point/fixed.hpp"
#include "fixed_point/fixed_math.hpp"
#include "fixed_point/simd.hpp"
#include "fixed_point/simd_math.hpp"

#include <nsimd/nsimd.h>

namespace nsimd
{
namespace fixed_point
{
template <uint8_t lf, uint8_t rt>
struct pack
{
  fpsimd_t<lf, rt> val;
};

template <uint8_t lf, uint8_t rt>
NSIMD_INLINE pack<lf, rt> add(pack<lf, rt> a0, pack<lf, rt> a1)
{
  pack<lf, rt> res;
  res.val = simd_add<lf, rt>(a0, a1);
  return res;
}

template <uint8_t lf, uint8_t rt>
NSIMD_INLINE pack<lf, rt> loadu(fp_t<lf, rt> *a)
{
  pack<lf, rt> res;
  res.val = simd_loadu<lf, rt>(a);
  return res;
}

template <uint8_t lf, uint8_t rt>
NSIMD_INLINE pack<lf, rt> mul(pack<lf, rt> a0, pack<lf, rt> a1)
{
  pack<lf, rt> res;
  res.val = simd_mul<lf, rt>(a0, a1);
  return res;
}

template <uint8_t lf, uint8_t rt>
NSIMD_INLINE void storeu(nsimd::fixed_point::fp_t<lf, rt> *a, pack<lf, rt> &p)
{
  simd_storeu<lf, rt>(a, p.val);
}

template <uint8_t lf, uint8_t rt>
NSIMD_INLINE pack<lf, rt> sub(pack<lf, rt> a0, pack<lf, rt> a1)
{
  pack<lf, rt> res;
  res.val = simd_sub<lf, rt>(a0, a1);
  return res;
}

} // namespace fixed_point
} // namespace nsimd

#endif