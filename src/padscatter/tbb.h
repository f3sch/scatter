#ifndef PAD_SCATTER_TBB
#define PAD_SCATTER_TBB

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/tbb.h>
#include <range/v3/view/zip.hpp>

namespace pad::tbb_simple
{

/*
 * tbb simple scatter using a zip iterator as a convenient tool to split the
 * ranges appropriately
 */
template <typename OutIt_t, typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng)
{
  using namespace ranges::views;
  using namespace oneapi;

  auto serial_scatter = [=](const auto &subrange) {
    for (const auto &[val, idx] : subrange) {
      outIt[idx] = val;
    }
  };
  auto z = zip(inRng, idxRng);
  ::tbb::parallel_for(::tbb::blocked_range{ z.begin(), z.end() },
                      serial_scatter);
}

} // namespace pad::tbb

#endif
