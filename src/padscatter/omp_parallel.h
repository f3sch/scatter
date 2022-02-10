#ifndef OMP_PARALLEL_H_
#define OMP_PARALLEL_H_

#include <cassert>
#include <omp.h>

namespace pad::omp::parallel
{

/*
 * Scatter using the builtin assembler mappings.
 * Only works with floats and a shuffle chunksize of 16!
 * https://godbolt.org/z/s8vaKPsYj-> vectorization on skylake and epyc
 */
template <typename Vec_t, typename Idx_t>
void scatter(Vec_t &out, const Vec_t &in, const Idx_t &idx,
             unsigned short nThreads = 0, omp_sched_t sched = omp_sched_static,
             int chunk_size = 1) noexcept
{
  int j;
  auto a = out.data();
  auto b = idx.data();
  auto c = in.data();
  auto N = static_cast<int>(idx.size()); // max is 2^30
  assert(N % 16 == 0);

  // set number of threads
  if (nThreads != 0) {
    omp_set_num_threads(nThreads);
  }

  // set scheduler and chunksize
  if (sched != omp_sched_static or chunk_size != 1) {
    omp_set_schedule(sched, chunk_size);
  }

#pragma omp parallel for private(j)
  for (auto i = 0; i < N; i += 16) {
#pragma omp simd aligned(a, b, c) safelen(16)
    for (j = 0; j < 16; ++j) {
      a[b[i + j]] = c[i + j];
    }
  }
}
} // namespace pad::omp::parallel

#endif // OMP_PARALLEL_H_
