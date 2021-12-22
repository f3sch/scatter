#ifndef PAD_SCATTER
#define PAD_SCATTER

#include <cassert>
#include <iterator>
#include <oneapi/tbb.h>
#include <ranges>

namespace pad {

/*
 * Simple and stupid serial scatter
 */
template <std::random_access_iterator OutIt_t, std::ranges::input_range InRng_t,
          std::ranges::input_range IdxRng_t>
void serial_scatter(OutIt_t outIt, const InRng_t &inRng,
                    const IdxRng_t &idxRng) {
  using namespace std;
  auto inIt = begin(inRng);
  auto inEnd = end(inRng);
  auto idxIt = begin(idxRng);
  auto idxEnd = end(idxRng);
  for (; inIt != inEnd && idxIt != idxEnd; ++inIt, ++idxIt) {
    auto j = *idxIt;
    assert(0 <= j && j < std::ranges::size(idxRng));
    *(outIt + j) = *inIt;
  }
}

} // end namespace pad

#endif
