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
  auto a = out.data(); // out ptr
  auto b = idx.data(); // idx ptr
  auto c = in.data(); // in ptr
  auto N = idx.size(); // idx size
  assert(in.size() % 16 == 0); // always fulfilled in our benchmarks
  for (auto i = 0; i + 15 < N; i += 16) {
    _mm512_i32scatter_ps(a, _mm512_loadu_epi32(b + i), _mm512_loadu_ps(c + i),
                         4);
  }
}
} // namespace pad::serial_intr_simd

#endif // SERIAL_INTR_SIMD_H_
