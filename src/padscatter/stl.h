#ifndef PAD_SCATTER_STL
#define PAD_SCATTER_STL

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/dpl/iterator>
#include <ranges>

namespace pad::stl {

/*
 * STL simple scatter using a zip iterator as a convenient tool to use for_each
 */
template <::std::random_access_iterator OutIt_t,
          ::std::ranges::input_range InRng_t,
          ::std::ranges::input_range IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng) {
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

} // namespace pad::stl

#endif
