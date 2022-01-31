#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialSimple(benchmark::State &state)
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
BENCHMARK(benchSerialSimple)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSerialSimpleLocal(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0));
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
BENCHMARK(benchSerialSimpleLocal)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

BENCHMARK_MAIN();
