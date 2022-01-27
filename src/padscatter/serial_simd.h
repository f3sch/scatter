//
// Created by anton on 1/5/22.
//

#ifndef SERIAL_SIMD_SCATTER_H
#define SERIAL_SIMD_SCATTER_H

//#define __AVX512F__ 1

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/tbb.h>
#include <future>
#include <array>
#include <vector>
#include <UMESimd.h>

#include <range/v3/view/zip.hpp>

namespace pad {

namespace serial_simd {
/*
 * Simple and stupid serial scatter with loop unrolling
 */
template <typename OutIt_t, typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outBegin, const InRng_t &inRng, const IdxRng_t &idxRng) {
	using namespace std;
	auto inIt = begin(inRng);
	auto inEnd = end(inRng);
	auto idxIt = begin(idxRng);
	auto idxEnd = end(idxRng);
  using Val_t = std::ranges::range_value_t<InRng_t>;
  using Idx_t = std::ranges::range_value_t<IdxRng_t>;

#ifndef __AVX512F__
  std::cerr << "Cannot run without AVX512 extensions. Aborting." << std::endl;
  abort();
#endif

	constexpr std::size_t simd_size = 8;
	assert(::ranges::size(inRng) % simd_size == 0);
	for (; inIt != inEnd && idxIt != idxEnd; inIt += simd_size, idxIt += simd_size) {
    UME::SIMD::SIMDVec<Idx_t, simd_size> j;
    UME::SIMD::SIMDVec<Val_t, simd_size> val;
    j.load(&*idxIt);
    val.load(&*inIt);
    val.scatter(&*outBegin, j);
  }
}

} // namespace serial


} // end namespace pad



#endif //SERIAL_SIMD_SCATTER_H
