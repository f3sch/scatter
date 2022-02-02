#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>
#include "benchmarks.h"

using namespace pad::benchmarks;

TEST(bench, locality)
{
  auto [_data, index] = makeChunkedPermutation(100, 42);
}

TEST(bench, simul)
{
  auto [_data, index] = makeChunkedPermutation(100, 42, 0.7);
}
