//
// Created by anton on 2/2/22.
//

#ifndef TBB_BINNING_H
#define TBB_BINNING_H

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/tbb.h>
#include <range/v3/view/zip.hpp>

#include "serial_binning.h"

namespace pad::tbb_binning
{

namespace direct_mapping
{
/*
 * tbb simple scatter using a zip iterator as a convenient tool to split the
 * ranges appropriately
 */
template <size_t chunkSize = 1024, size_t binSize = 64,
    size_t cacheLineSize = 64, size_t bankCount = 8, typename OutIt_t,
    typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng)
{
  using namespace ranges::views;
  using namespace oneapi;

  auto serial_scatter = [=](const auto &subrange) {
    pad::serial_binning::direct_mapping::scatter<chunkSize, binSize, cacheLineSize, bankCount>(outIt, subrange);
  };
  auto z = zip(inRng, idxRng);
  ::tbb::parallel_for(::tbb::blocked_range{ z.begin(), z.end() },
                      serial_scatter);
}
}

namespace fully_associative
{
/*
 * tbb simple scatter using a zip iterator as a convenient tool to split the
 * ranges appropriately
 */
template <size_t chunkSize = 1024, size_t binSize = 64, typename OutIt_t,
    typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng)
{
  using namespace ranges::views;
  using namespace oneapi;

  auto serial_scatter = [=](const auto &subrange) {
          pad::serial_binning::fully_associative::scatter<chunkSize, binSize>(outIt, subrange);
  };
  auto z = zip(inRng, idxRng);
  ::tbb::parallel_for(::tbb::blocked_range{ z.begin(), z.end() },
                      serial_scatter);
}
}

} // namespace pad::tbb

#endif //TBB_BINNING_H
