//
// Created by anton on 1/5/22.
//

#ifndef TBB_PRESORT_H
#define TBB_PRESORT_H

#include "serial.h"

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/tbb.h>
#include <future>
#include <ranges>
#include <array>
#include <vector>

#include <range/v3/view/zip.hpp>

namespace pad {

namespace tbb_presort {

namespace detail
{
inline size_t log2(size_t x)
{
  return __builtin_ctz(x);
}
}

/**
* Convenient and safe API for Divide and Conquer optimized scatter.
* Input and temporary buffers need to be moved in as this algorithm
* is destructive wrt the input data. It returns the output buffer
* in form of a std::vector.
*/
template<size_t baseCaseThreshold = 1024,
	size_t subdivisionExponent = 5,
	size_t parallelism = 8,
	std::random_access_iterator OutIt_t,
  std::ranges::contiguous_range InRng_t,
  std::ranges::contiguous_range IdxRng_t>
void scatter(OutIt_t outBegin, const InRng_t &in, const IdxRng_t &idx, InRng_t &tmp, IdxRng_t &tmpIdx)
{
	using namespace std;
	auto N = size(in);
	assert(size(idx) == N);
	assert(size(tmp) == N);
	assert(size(tmpIdx) == N);

	std::array<size_t, parallelism> bins;
	auto bitShift = detail::log2(N) - detail::log2(parallelism);
	auto step = 1 << bitShift;
	auto tmpBegin = begin(tmp);
	auto tmpIdxBegin = begin(tmpIdx);
	for (size_t i = 0; i < parallelism; ++i) {
		bins[i] = i*step;
	}

	auto inBegin = begin(in);
	auto inIt = inBegin;
	auto inEnd = end(in);
	auto idxIt = begin(idx);
	for (; inIt != inEnd; ++inIt, ++idxIt) {
		auto j = *idxIt;
		auto val = *inIt;
		auto binIdx = j >> bitShift;
		assert(j >= 0 && j < N);
    tmpBegin[bins[binIdx]] = val;
    tmpIdxBegin[bins[binIdx]] = j - binIdx*step;
    ++bins[binIdx];
	}

	oneapi::tbb::task_group g;

	for( size_t i = 0; i < parallelism; ++i ) {
    auto task = [
      outBegin = outBegin + i * step,
      in = std::ranges::subrange(tmpBegin + i * step, tmpBegin + (i + 1) * step),
      idx = std::ranges::subrange(tmpIdxBegin + i * step, tmpIdxBegin + (i + 1) * step)
    ] {
      pad::serial::scatter(outBegin, in, idx);
    };

		g.run(task);
	}
	// Wait for recursive calls to complete
	g.wait();
}


}

} // end namespace pad

#endif //TBB_PRESORT_H
