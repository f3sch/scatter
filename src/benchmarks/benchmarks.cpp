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
void benchLocalityArgs(benchmark::internal::Benchmark *b)
{
  const auto locality_lowerLimit = 1;
  const auto locality_uppperLimit = 10;
  const auto size = 1 << 24;
  for (auto i = locality_lowerLimit; i <= locality_uppperLimit; ++i) {
    b->Args({ size, 1 << i });
  }
}

void benchGrainArgs(benchmark::internal::Benchmark *b)
{
  const auto lowerLimit = 0;
  const auto uppperLimit = 27;
  for (auto i = lowerLimit; i <= uppperLimit; ++i) {
    b->Args({ 1 << i });
  }
}

void benchPartitionArgs(benchmark::internal::Benchmark *b)
{
  const auto lowerLimit = 10;
  const auto uppperLimit = 27;
  for (auto i = lowerLimit; i <= uppperLimit; ++i) {
    b->Args({ 1 << i });
  }
}

void benchOmpArgs(benchmark::internal::Benchmark *b)
{
  const auto lowerLimitChunk = 1;
  const auto uppperLimitChunk = 5;
  const auto lowerLimitSize = 5;
  const auto uppperLimitSize = 10;
  const auto lowerLimitThreads = 0;
  const auto uppperLimitThreads = 32;
  for (auto k = lowerLimitThreads; k <= uppperLimitThreads;
       (k == 0) ? k = 1 : k *= 2) {
    for (auto i = lowerLimitSize; i <= uppperLimitSize; ++i) {
      for (auto j = lowerLimitChunk; i <= uppperLimitChunk; ++i) {
        b->Args({ 1 << i, 1 << j, k });
      }
    }
  }
}

void benchCounters(benchmark::State &state)
{
  state.counters["Elements"] = state.range(0);
  // Scatter: y[idx[i]] = x[i]
  // is comprised of reading idx[i], x[i] and writing to y[idx[i]]
  // 3 operations
  // GOP has to be divided by the time to get GOPS
  auto GOP = int64_t(state.iterations()) * int64_t(state.range(0)) * 3;
  state.counters["GOP"] = GOP;
  state.counters["GOPperIter"] = GOP / state.iterations();
  state.counters["Bytes_processed"] =
      state.range(0) * (2 * sizeof(DataType) + sizeof(Index));
}

void benchGrainCounters(benchmark::State &state)
{
  state.counters["Grainsize"] = state.range(0);
}

void benchOmpCounters(benchmark::State &state)
{
  state.counters["Elements"] = state.range(0);
  state.counters["ChunkSize"] = state.range(1);
  state.counters["Threads"] = state.range(2);
}

} // namespace pad::benchmarks
