#include "benchmarks.h"
#include "serial.h"
#include <algorithm>
#include <array>
#include <benchmark/benchmark.h>
#include <chrono>
#include <tbb/parallel_for.h>
#include <vector>
#include <iostream>
#include <range/v3/view/take.hpp>

namespace pad::benchmarks
{

bool cmpFloat(DataType a, DataType b, DataType eps)
{
  return fabs(a - b) <= eps;
}

void verifyScatter(DataVec inVec, IndexVec index, DataVec out)
{
  DataVec correct(inVec.size());
  pad::serial::scatter(correct.begin(), inVec, index);
  for (Index i = 0; i < inVec.size(); i++) {
    if (!cmpFloat(out[i], correct[i])) {
      std::cerr << "Output vectors are not equal!" << std::endl;
      std::cerr << "Indices: ";
      for (auto &&idx : index | ::ranges::views::take(10)) {
        std::cerr << idx << ", ";
      }
      std::cerr << std::endl;
      std::cerr << "In: ";
      for (auto &&val : inVec | ::ranges::views::take(10)) {
        std::cerr << val << ", ";
      }
      std::cerr << std::endl;
      std::cerr << "Actual: ";
      for (auto &&val : out | ::ranges::views::take(10)) {
        std::cerr << val << ", ";
      }
      std::cerr << std::endl;
      std::cerr << "Expected: ";
      for (auto &&val : correct | ::ranges::views::take(10)) {
        std::cerr << val << ", ";
      }
      std::cerr << std::endl;
      throw std::runtime_error("Wrong Results");
    }
  }
}

void benchArgs(benchmark::internal::Benchmark *b)
{
  const auto lowerLimit = 15;
  const auto uppperLimit = 30;
  for (auto i = lowerLimit; i <= uppperLimit; ++i) {
    b->Args({ 1 << i });
  }
}

void benchCounters(benchmark::State &state)
{
  state.counters["Elements"] = state.range(0);
  auto GOPS = int64_t(state.iterations()) * int64_t(state.range(0));
  state.counters["GOPS"] = GOPS;
  state.counters["GOPSperIter"] = GOPS / state.iterations();
  state.counters["Bytes_processed"] =
      2 * state.range(0) * sizeof(DataType) + sizeof(Index);
}

} // namespace pad::benchmarks
