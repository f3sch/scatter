#ifndef TBB_SCAN_H_
#define TBB_SCAN_H_

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/tbb.h>
#include <future>
#include <array>
#include <vector>

#include <range/v3/view/subrange.hpp>
#include <range/v3/size.hpp>

namespace pad::tbb::scan
{

namespace internal
{

template <typename T> inline bool check_range(T value, T min, T max)
{
  return (value >= min) && (value < max);
}

} // namespace internal

/**
 * Implementing the multipass scatter, suggested [[here][https://cse.hkust.edu.hk/catalac/papers/scatter_sc07.pdf]].
 * This should improve write locality _dramatically_ (probably screwed it up tho).
 * This is the tbb version, meaning that instead of doing multiple passes, we are doing it in parallel.
 * Since the passes are independent of each other, this should prove to be an improvement.
 */
template <typename OutIt_t, typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng,
             size_t sizePartition = 1024)
{
  // check boundaries
  auto N = ranges::size(inRng);
  assert(ranges::size(idxRng) == N);

  // partition
  size_t partitions =
      (N % sizePartition == 0) ? N / sizePartition : N / sizePartition + 1;

  // thread function
  auto func = [&](oneapi::tbb::blocked_range<size_t> r) {
    for (auto i = r.begin(); i < r.end(); ++i) {
      auto inIt = begin(inRng);
      auto inEnd = end(inRng);
      auto idxIt = begin(idxRng);
      auto idxEnd = end(idxRng);
      for (; inIt != inEnd && idxIt != idxEnd; ++inIt, ++idxIt) {
        auto j = *idxIt;
        if (internal::check_range<size_t>(j, i * sizePartition,
                                          (i + 1) * sizePartition))
          *(outIt + j) = *inIt;
      }
    }
  };

  oneapi::tbb::parallel_for(oneapi::tbb::blocked_range<size_t>(0, partitions),
                            func);
}
} // namespace pad::tbb::scan

#endif // TBB_SCAN_H_
