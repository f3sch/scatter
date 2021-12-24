#ifndef PAD_SCATTER
#define PAD_SCATTER

#include <cassert>
#include <iterator>
#include <oneapi/dpl/iterator>
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

/*
 * tbb simple scatter using a zip iterator as a convenient tool to split the
 * ranges appropriately
 */
template <std::random_access_iterator OutIt_t, std::ranges::input_range InRng_t,
          std::ranges::input_range IdxRng_t>
void tbb_scatter_simple(OutIt_t outIt, const InRng_t &inRng,
                        const IdxRng_t &idxRng) {
  using namespace std;
  using namespace oneapi;
  auto zbegin = dpl::make_zip_iterator(begin(inRng), begin(idxRng));
  auto zend = dpl::make_zip_iterator(end(inRng), end(idxRng));
  tbb::parallel_for(tbb::blocked_range<decltype(zbegin)>(zbegin, zend),
                    [=](const tbb::blocked_range<decltype(zbegin)> &r) {
                      for (auto zIt = r.begin(); zIt != r.end(); zIt++) {
                        auto [val, j] = *zIt;
                        assert(0 <= j && j < std::ranges::size(idxRng));
                        *(outIt + j) = val;
                      }
                    });
}

} // end namespace pad

#endif
