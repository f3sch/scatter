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
  pad::serial::scatter(input_scattered.begin(), input, indices);

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
  pad::serial::scatter(input_scattered.begin(), input, indices);
  std::vector<unsigned int> correct = {3, 5, 10, 7, 1, 4, 2, 8, 9, 6, 0};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the simple serial scatter using doubles
 */
TEST(serial_scatter, doubles) {
  std::vector<double> input = {0.0, 1.1, 2.2, 3.3, 4.4,  5.5,
                               6.6, 7.7, 8.8, 9.9, 10.10};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<double> input_scattered = input;
  pad::serial::scatter(input_scattered.begin(), input, indices);
  std::vector<double> correct = {3.3, 5.5, 10.10, 7.7, 1.1, 4.4,
                                 2.2, 8.8, 9.9,   6.6, 0.0};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the simple serial scatter using floats
 */
TEST(serial_scatter, floats) {
  std::vector<float> input = {0.0f, 1.1f, 2.2f, 3.3f, 4.4f,  5.5f,
                              6.6f, 7.7f, 8.8f, 9.9f, 10.10f};
  std::vector<float> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<float> input_scattered = input;
  pad::serial::scatter(input_scattered.begin(), input, indices);
  std::vector<float> correct = {3.3f, 5.5f, 10.10f, 7.7f, 1.1f, 4.4,
                                2.2f, 8.8f, 9.9f,   6.6f, 0.0f};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the tbb simple scatter using strings
 */
TEST(std_scatter, string_simple) {
  std::string input = "Lorem ipsum";
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::string input_scattered = input;
  pad::stl::scatter(input_scattered.begin(), input, indices);

  EXPECT_EQ(input_scattered, "e mpomrsuiL");
}

/*
 * Test for the tbb simple scatter using uints
 */
TEST(std_scatter, uints) {
  std::vector<unsigned int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<unsigned int> input_scattered = input;
  pad::stl::scatter(input_scattered.begin(), input, indices);
  std::vector<unsigned int> correct = {3, 5, 10, 7, 1, 4, 2, 8, 9, 6, 0};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the tbb simple scatter using doubles
 */
TEST(std_scatter, doubles) {
  std::vector<double> input = {0.0, 1.1, 2.2, 3.3, 4.4,  5.5,
                               6.6, 7.7, 8.8, 9.9, 10.10};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<double> input_scattered = input;
  pad::stl::scatter(input_scattered.begin(), input, indices);
  std::vector<double> correct = {3.3, 5.5, 10.10, 7.7, 1.1, 4.4,
                                 2.2, 8.8, 9.9,   6.6, 0.0};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the tbb simple scatter using floats
 */
TEST(std_scatter, floats) {
  std::vector<float> input = {0.0f, 1.1f, 2.2f, 3.3f, 4.4f,  5.5f,
                              6.6f, 7.7f, 8.8f, 9.9f, 10.10f};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<float> input_scattered = input;
  pad::stl::scatter(input_scattered.begin(), input, indices);
  std::vector<float> correct = {3.3f, 5.5f, 10.10f, 7.7f, 1.1f, 4.4,
                                2.2f, 8.8f, 9.9f,   6.6f, 0.0f};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the tbb simple scatter using strings
 */
TEST(tbb_scatter, string_simple) {
  std::string input = "Lorem ipsum";
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::string input_scattered = input;
  pad::tbb::scatter_simple(input_scattered.begin(), input, indices);

  EXPECT_EQ(input_scattered, "e mpomrsuiL");
}

/*
 * Test for the tbb simple scatter using uints
 */
TEST(tbb_scatter, uints) {
  std::vector<unsigned int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<unsigned int> input_scattered = input;
  pad::tbb::scatter_simple(input_scattered.begin(), input, indices);
  std::vector<unsigned int> correct = {3, 5, 10, 7, 1, 4, 2, 8, 9, 6, 0};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the tbb simple scatter using doubles
 */
TEST(tbb_scatter, doubles) {
  std::vector<double> input = {0.0, 1.1, 2.2, 3.3, 4.4,  5.5,
                               6.6, 7.7, 8.8, 9.9, 10.10};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<double> input_scattered = input;
  pad::tbb::scatter_simple(input_scattered.begin(), input, indices);
  std::vector<double> correct = {3.3, 5.5, 10.10, 7.7, 1.1, 4.4,
                                 2.2, 8.8, 9.9,   6.6, 0.0};
  EXPECT_EQ(input_scattered, correct);
}

/*
 * Test for the tbb simple scatter using floats
 */
TEST(tbb_scatter, floats) {
  std::vector<float> input = {0.0f, 1.1f, 2.2f, 3.3f, 4.4f,  5.5f,
                              6.6f, 7.7f, 8.8f, 9.9f, 10.10f};
  std::vector<size_t> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::shuffle(indices.begin(), indices.end(), std::mt19937{0});

  std::vector<float> input_scattered = input;
  pad::tbb::scatter_simple(input_scattered.begin(), input, indices);
  std::vector<float> correct = {3.3f, 5.5f, 10.10f, 7.7f, 1.1f, 4.4,
                                2.2f, 8.8f, 9.9f,   6.6f, 0.0f};
  EXPECT_EQ(input_scattered, correct);
}
