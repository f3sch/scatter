#include "scatter.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>

/*
 * Test for the simpel serial scatter using strings
 */
TEST(serial_scatter, string_simple) {
  std::string input = "Lorem ipsum";
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::string input_scattered = input;
  pad::serial_scatter(input_scattered.begin(), input, indices);

  EXPECT_EQ(input_scattered, "e mpomrsuiL");
}

/*
 * Test for the simple serial scatter using uints
 */
TEST(serial_scatter, uints) {
  std::vector<unsigned int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<unsigned int> input_scattered = input;
  pad::serial_scatter(input_scattered.begin(), input, indices);
  std::vector<unsigned int> correct = {3, 5, 10, 7, 1, 4, 2, 8, 9, 6, 0};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the tbb scatter using strings
 */
TEST(tbb_scatter, string_simple) {
  std::string input = "Lorem ipsum";
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::string input_scattered = input;
  pad::tbb_scatter(input_scattered.begin(), input, indices);

  EXPECT_EQ(input_scattered, "e mpomrsuiL");
}

/*
 * Test for the tbb scatter using uints
 */
TEST(tbb_scatter, uints) {
  std::vector<unsigned int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<unsigned int> input_scattered = input;
  pad::tbb_scatter(input_scattered.begin(), input, indices);
  std::vector<unsigned int> correct = {3, 5, 10, 7, 1, 4, 2, 8, 9, 6, 0};
  EXPECT_EQ(input_scattered, correct);
}
