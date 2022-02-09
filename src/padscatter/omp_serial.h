#ifndef OMP_SERIAL_H_
#define OMP_SERIAL_H_

#include <cassert>
#include <omp.h>

namespace pad::omp::serial
{

/*
 * Scatter using the builtin assembler mappings.
 * Only works with floats and a shuffle chunksize of 16!
 * https://godbolt.org/z/Yb9fG3b6c -> vectorization on skylake and epyc
 */
template <typename Vec_t, typename Idx_t>
void scatter(Vec_t &out, const Vec_t &in, const Idx_t &idx) noexcept
{
  int j;
  auto a = out.data();
  auto b = idx.data();
  auto c = in.data();
  auto N = static_cast<int>(idx.size()); // max is 2^30
  assert(N % 16 == 0);

  for (auto i = 0; i < N; i += 16) {
#pragma omp simd aligned(a, b, c) safelen(16)
    for (j = 0; j < 16; ++j) {
      a[b[i + j]] = c[i + j];
    }
  }
}
} // namespace pad::omp::serial

#endif // OMP_SERIAL_H_
