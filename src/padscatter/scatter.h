#ifndef PAD_SCATTER
#define PAD_SCATTER

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/dpl/iterator>
#include <oneapi/tbb.h>
#include <ranges>

namespace pad {

namespace serial {
/*
 * Simple and stupid serial scatter
 */
template <std::random_access_iterator OutIt_t, std::ranges::input_range InRng_t,
          std::ranges::input_range IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng) {
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

} // namespace serial

namespace std {

/*
 * std simple scatter using a zip iterator as a convenient tool to use for_each
 */
template <::std::random_access_iterator OutIt_t,
          ::std::ranges::input_range InRng_t,
          ::std::ranges::input_range IdxRng_t>
void scatter_simple(OutIt_t outIt, const InRng_t &inRng,
                    const IdxRng_t &idxRng) {
  using namespace oneapi;
  auto zbegin =
      dpl::make_zip_iterator(::std::begin(inRng), ::std::begin(idxRng));
  auto zend = dpl::make_zip_iterator(::std::end(inRng), ::std::end(idxRng));
  ::std::for_each(::std::execution::par_unseq, zbegin, zend, [=](auto zIt) {
    auto [val, j] = zIt;
    assert(0 <= j && j < ::std::ranges::size(idxRng));
    *(outIt + j) = val;
  });
}

} // namespace std

namespace tbb {

/*
 * tbb simple scatter using a zip iterator as a convenient tool to split the
 * ranges appropriately
 */
template <::std::random_access_iterator OutIt_t,
          ::std::ranges::input_range InRng_t,
          ::std::ranges::input_range IdxRng_t>
void scatter_simple(OutIt_t outIt, const InRng_t &inRng,
                    const IdxRng_t &idxRng) {
  using namespace std;
  using namespace oneapi;
  auto zbegin = dpl::make_zip_iterator(begin(inRng), begin(idxRng));
  auto zend = dpl::make_zip_iterator(end(inRng), end(idxRng));
  ::tbb::parallel_for(::tbb::blocked_range<decltype(zbegin)>(zbegin, zend),
                      [=](const ::tbb::blocked_range<decltype(zbegin)> &r) {
                        for (auto zIt = r.begin(); zIt != r.end(); zIt++) {
                          auto [val, j] = *zIt;
                          assert(0 <= j && j < ::std::ranges::size(idxRng));
                          *(outIt + j) = val;
                        }
                      });
}

} // namespace tbb

} // end namespace pad

#endif
