#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialScan(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial::scan::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialScan)->Apply(pad::benchmarks::benchArgs)->UseRealTime();
BENCHMARK_MAIN();
