#ifndef SERIAL_INTR_SIMD_H_
#define SERIAL_INTR_SIMD_H_

#include <immintrin.h>
#include <cassert>
#include <range/v3/all.hpp>

namespace pad::serial_intr_simd
{

/*
 * Scatter using the builtin assembler mappings.
 * Only works with floats and a shuffle chunksize of 16!
 */
template <typename Vec_t, typename Idx_t>
void scatter(Vec_t &out, const Vec_t &in, const Idx_t &idx)
{
  assert(in.size() % 16 == 0);

  for (long unsigned int out_off = 0; out_off < out.size(); out_off += 16) {
    //load index array
    __m512i vidx = _mm512_loadu_epi32(idx.data() + out_off);
    //load input array
    __m512 vin = _mm512_loadu_ps(in.data() + out_off);
    //perform scatter
    _mm512_i32scatter_ps(out.data() + out_off, vidx, vin, sizeof(float));
  }
}
} // namespace pad::serial_intr_simd

#endif // SERIAL_INTR_SIMD_H_
