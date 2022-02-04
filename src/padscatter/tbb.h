#ifndef PAD_SCATTER_TBB
#define PAD_SCATTER_TBB

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/tbb.h>
#include <range/v3/view/zip.hpp>

namespace pad::tbb_simple
{

using namespace ranges::views;
using namespace oneapi::tbb;
/*
 * tbb simple scatter using a zip iterator as a convenient tool to split the
 * ranges appropriately
 */
template <typename OutIt_t, typename InRng_t, typename IdxRng_t,
          typename Partitioner = auto_partitioner>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng,
             const size_t grainsize = 1,
             Partitioner partitioner = auto_partitioner())
{
  auto serial_scatter = [=](const auto &subrange) {
    for (const auto &[val, idx] : subrange) {
      outIt[idx] = val;
    }
  };
  auto z = zip(inRng, idxRng);
  parallel_for(blocked_range{ z.begin(), z.end(), grainsize }, serial_scatter,
               partitioner);
}

} // namespace pad::tbb_simple

#endif
