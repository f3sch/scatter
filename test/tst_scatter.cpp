#include "scatter.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>

TEST(serial_scatter, string_simple) {
  std::string input = "Lorem ipsum";
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::string input_scattered = input;
  pad::serial_scatter(input_scattered.begin(), input, indices);

  EXPECT_EQ(input_scattered, "e mpomrsuiL");
}
