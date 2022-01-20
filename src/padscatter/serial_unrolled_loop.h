//
// Created by anton on 1/5/22.
//

#ifndef SERIAL_UNROLLED_LOOP_H
#define SERIAL_UNROLLED_LOOP_H

#include <cassert>
#include <execution>
#include <iterator>
#include <oneapi/tbb.h>
#include <future>
#include <array>
#include <vector>
#include <range/v3/size.hpp>

namespace pad
{

namespace serial_unrolled_loop
{
/*
 * Simple and stupid serial scatter with loop unrolling
 */
template <typename OutIt_t, typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng)
{
  using namespace std;
  auto inIt = begin(inRng);
  auto inEnd = end(inRng);
  auto idxIt = begin(idxRng);
  auto idxEnd = end(idxRng);
  //	auto N = std::size(inRng);

  constexpr std::size_t simd_size = 8;
  assert(::ranges::size(inRng) % simd_size == 0);
  //	std::size_t vec_size = N - N % simd_size;
  for (; inIt != inEnd && idxIt != idxEnd;
       inIt += simd_size, idxIt += simd_size) {
    auto j0 = idxIt[0];
    auto j1 = idxIt[1];
    auto j2 = idxIt[2];
    auto j3 = idxIt[3];
    auto j4 = idxIt[4];
    auto j5 = idxIt[5];
    auto j6 = idxIt[6];
    auto j7 = idxIt[7];
    auto val0 = inIt[0];
    auto val1 = inIt[1];
    auto val2 = inIt[2];
    auto val3 = inIt[3];
    auto val4 = inIt[4];
    auto val5 = inIt[5];
    auto val6 = inIt[6];
    auto val7 = inIt[7];
    assert(0 <= j0 && j0 < ::ranges::size(idxRng));
    assert(0 <= j1 && j1 < ::ranges::size(idxRng));
    assert(0 <= j2 && j2 < ::ranges::size(idxRng));
    assert(0 <= j3 && j3 < ::ranges::size(idxRng));
    (outIt + j0)[0] = val0;
    (outIt + j1)[1] = val1;
    (outIt + j2)[2] = val2;
    (outIt + j3)[3] = val3;
    (outIt + j4)[4] = val4;
    (outIt + j5)[5] = val5;
    (outIt + j6)[6] = val6;
    (outIt + j7)[7] = val7;
  }
}

} // namespace serial_unrolled_loop

} // end namespace pad

#endif //SERIAL_UNROLLED_LOOP_H
