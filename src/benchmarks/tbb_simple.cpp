#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchTbbSimple(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_simple::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbSimple)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchTbbSimpleChunkedPermutation(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeChunkedPermutation(state.range(0),  state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_simple::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbSimpleChunkedPermutation)
    ->Apply(pad::benchmarks::benchLocalityArgs)
    ->UseRealTime();

static void benchTbbSimpleNormalDistributedShuffle(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_simple::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbSimpleNormalDistributedShuffle)
    ->Apply(pad::benchmarks::benchLocalityArgs)
    ->UseRealTime();

BENCHMARK_MAIN();
