#ifndef PAD_SCATTER_SERIAL
#define PAD_SCATTER_SERIAL

#include <cassert>
#include <iterator>
#include <range/v3/size.hpp>

namespace pad::serial
{

/*
 * Simple and stupid serial scatter
 */
template <typename OutIt_t, typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, InRng_t &inRng, IdxRng_t &idxRng)
{
  using namespace std;
  auto inIt = begin(inRng);
  auto inEnd = end(inRng);
  auto idxIt = begin(idxRng);
  auto idxEnd = end(idxRng);
  for (; inIt != inEnd && idxIt != idxEnd; ++inIt, ++idxIt) {
    auto j = *idxIt;
    assert(0 <= j && j < ::ranges::size(idxRng));
    *(outIt + j) = *inIt;
  }
}
} // namespace pad::serial

#endif
