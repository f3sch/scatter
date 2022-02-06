//
// Created by anton on 2/3/22.
//

#include <range/v3/all.hpp>
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <ranges>
#include "benchmarks.h"

/**
 * Tests whether the linear_congruential_permutation_engine used for the
 * "computed data" benchmarks actually fullfills the requirement of being a
 * permutation, i.e. it yields every index between 0 and N exactly once.
 */
TEST(test_linear_congruential_permutation_engine, blah )
{
  for (size_t n = 1 << 15; n < 1 << 30; n *= 2) {
    auto lce = linear_congruential_permutation_engine { n, 461887 };
    auto v = ranges::views::generate_n(lce, n)
             | ranges::to_vector;
    ranges::actions::sort(v);

//    ranges::copy(v | ranges::views::take(64), ranges::ostream_iterator<size_t>(std::cout, ", "));
//    std::cout << std::endl;

    EXPECT_TRUE(ranges::equal(v, ranges::views::iota(0ul, n)));
  }
}
