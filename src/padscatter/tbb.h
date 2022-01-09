#ifndef PAD_SCATTER_TBB
#define PAD_SCATTER_TBB

#include <cassert>
#include <execution>
#include <iterator>
//#include <oneapi/dpl/iterator>
#include <oneapi/tbb.h>
#include <ranges>
#include <range/v3/view/zip.hpp>

namespace pad::tbb {

/*
 * tbb simple scatter using a zip iterator as a convenient tool to split the
 * ranges appropriately
 */
template <::std::random_access_iterator OutIt_t,
          ::std::ranges::input_range InRng_t,
          ::std::ranges::input_range IdxRng_t>
void scatter_simple(OutIt_t outIt, const InRng_t &inRng,
                    const IdxRng_t &idxRng) {
//  using namespace std;
//  using namespace oneapi;
//  auto zbegin = dpl::make_zip_iterator(begin(inRng), begin(idxRng));
//  auto zend = dpl::make_zip_iterator(end(inRng), end(idxRng));
//  ::tbb::parallel_for(::tbb::blocked_range<decltype(zbegin)>(zbegin, zend),
//                      [=](const ::tbb::blocked_range<decltype(zbegin)> &r) {
//                        for (auto zIt = r.begin(); zIt != r.end(); zIt++) {
//                          auto [val, j] = *zIt;
//                          assert(0 <= j && j < ::std::ranges::size(idxRng));
//                          *(outIt + j) = val;
//                        }
//                      });

  using namespace ranges::views;

  auto serial_scatter = [=](const auto &subrange) {
          for (const auto &[val, idx] : subrange) {
            outIt[idx] = val;
          }
  };
  auto z = zip(inRng, idxRng);
  tbb::parallel_for(tbb::blocked_range{ z.begin(), z.end() }, serial_scatter);
}

} // namespace pad::tbb

#endif
