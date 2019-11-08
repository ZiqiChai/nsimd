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

#ifndef NSIMD_MODULES_FIXED_POINT_FUNCTION_SIMD_DIV_HPP
#define NSIMD_MODULES_FIXED_POINT_FUNCTION_SIMD_DIV_HPP

#include "nsimd/modules/fixed_point/simd.hpp"
#include <nsimd/nsimd.h>

namespace nsimd {
namespace fixed_point {

template <uint8_t _lf, uint8_t _rt>
NSIMD_INLINE fpsimd_uc<_lf,_rt> simd_div_uc( const fpsimd_uc<_lf,_rt> &a,
                                             const fpsimd_uc<_lf,_rt> &b ) {
  typedef typename fp_t<_lf, _rt>::value_up up_t;
  typedef typename fp_t<_lf, _rt>::value_type val_t;
  const int n_bits = 8 * sizeof(val_t);
  const int shift = n_bits - _lf;

  return fpsimd_uc<_lf,_rt>(
        nsimd::div(nsimd::shl(a._v1, shift, up_t()), b._v1, up_t())
      , nsimd::div(nsimd::shl(a._v2, shift, up_t()), b._v2, up_t())
      );
}

template <uint8_t _lf, uint8_t _rt>
NSIMD_INLINE fpsimd_t<_lf, _rt> simd_div(const fpsimd_t<_lf, _rt> &a,
                                         const fpsimd_t<_lf, _rt> &b) {
  fpsimd_uc<_lf,_rt> aa = simd_decompress( a );
  fpsimd_uc<_lf,_rt> bb = simd_decompress( b );

  aa = simd_div_uc( aa , bb );

  fpsimd_t<_lf,_rt> res = simd_compress( aa );
  return res;
}

// Operator overload with base type compatibility
template <uint8_t _lf, uint8_t _rt>
NSIMD_INLINE fpsimd_t<_lf, _rt> operator/(const fpsimd_t<_lf, _rt> &a,
                                          const fpsimd_t<_lf, _rt> &b) {
  return simd_div(a, b);
}

template <uint8_t _lf, uint8_t _rt>
NSIMD_INLINE fpsimd_uc<_lf, _rt> operator/(const fpsimd_uc<_lf, _rt> &a,
                                           const fpsimd_uc<_lf, _rt> &b) {
  return simd_div_uc(a, b);
}


} // namespace fixed_point
} // namespace nsimd

#endif