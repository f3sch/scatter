#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>
#include "benchmarks.h"

// not sure how to test this
TEST(bench, locality)
{
  using namespace pad::benchmarks;
  auto [_data, index] = makeDataLocal(100, 42);
}
