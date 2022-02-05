#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>
#include <iostream>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/iterator.hpp>

static void benchCopy(benchmark::State &state)
{
  auto N = state.range(0);
  pad::benchmarks::DataVec vec(N);
  pad::benchmarks::IndexVec index(N);
  pad::benchmarks::DataVec out(N);

  std::iota(vec.begin(), vec.end(), 0);
  std::iota(index.begin(), index.end(), 0);

  for (auto _ : state) {
    std::copy(vec.begin(), vec.end(), out.begin());
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchCopy)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSerialSimpleId(benchmark::State &state)
{
  auto N = state.range(0);
  pad::benchmarks::DataVec vec(N);
  pad::benchmarks::IndexVec index(N);
  pad::benchmarks::DataVec out(N);

  std::iota(vec.begin(), vec.end(), 0);
  std::iota(index.begin(), index.end(), 0);

  for (auto _ : state) {
    pad::serial::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimpleId)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSerialSimpleComputedId(benchmark::State &state)
{
  size_t N = state.range(0);
  auto out = pad::benchmarks::DataVec ( N );
  auto vec = ranges::views::iota(0ul, N);
  auto index = ranges::views::iota(0ul, N);

  for (auto _ : state) {
    pad::serial::scatter(out.begin(), vec, index);
    benchmark::ClobberMemory();
  }
//  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimpleComputedId)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSerialSimpleRandom(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  // verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimpleRandom)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSerialSimpleComputedRandom(benchmark::State &state)
{
  pad::benchmarks::Vec<size_t> out(state.range(0));
  for (auto _ : state) {
    auto [vec, index] = pad::benchmarks::makeComputedInput(state.range(0));
    pad::serial::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
//  ranges::copy(out | ranges::views::take(64), ranges::ostream_iterator<double>(std::cout, ", "));
  // verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimpleComputedRandom)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSerialSimpleChunkedPermutation(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeChunkedPermutation(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimpleChunkedPermutation)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialSimpleNormalDistributedShuffle(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimpleNormalDistributedShuffle)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

BENCHMARK_MAIN();
