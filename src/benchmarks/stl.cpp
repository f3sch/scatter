#include "benchmarks.h"
#include "stl.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSTLSimple(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::stl::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSTLSimple)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSTLSimpleLocal(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::stl::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSTLSimpleLocal)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

BENCHMARK_MAIN();
