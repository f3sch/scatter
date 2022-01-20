#ifndef SERIAL_SCAN_H_
#define SERIAL_SCAN_H_

#include <cassert>
#include <iterator>
#include <array>
#include <vector>

#include <range/v3/view/zip.hpp>
#include <range/v3/view/subrange.hpp>
#include <range/v3/size.hpp>

namespace pad::serial::scan
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
 */
template <size_t sizePartition = 1024, typename OutIt_t, typename InRng_t,
          typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng)
{
  // check boundaries
  auto N = ranges::size(inRng);
  assert(ranges::size(idxRng) == N);

  // partition
  size_t partitions =
      (N % sizePartition == 0) ? N / sizePartition : N / sizePartition + 1;

  for (size_t i = 0; i < partitions; ++i) {
    /*
     * We are doing multiple passes over our input ranges.
     * This seems to be unavoidable. Hopefully the prefetcher helps us here, with
     * sequential acccess patterns.
     */
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
}

} // namespace pad::serial::scan
#endif // SERIAL_SCAN_H_
