#ifndef PAD_SCATTER_STL
#define PAD_SCATTER_STL

#include <cassert>
#include <execution>
#include <iterator>
#include <ranges>
#include <range/v3/view/zip.hpp>
#include <range/v3/size.hpp>

namespace pad::stl {

/*
 * STL simple scatter using a zip iterator as a convenient tool to use for_each
 */
template <::std::random_access_iterator OutIt_t,
          ::std::ranges::input_range InRng_t,
          ::std::ranges::input_range IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng) {
  auto z = ranges::views::zip(inRng, idxRng);
  std::for_each(::std::execution::par_unseq, z.begin(), z.end(), [=](auto z) {
    auto [val, j] = z;
    assert(0 <= j && j < ranges::size(idxRng));
    *(outIt + j) = val;
  });
}

} // namespace pad::stl

#endif
