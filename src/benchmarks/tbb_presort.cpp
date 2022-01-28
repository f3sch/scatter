#include "benchmarks.h"
#include "tbb_presort.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchTbbPresort(benchmark::State &state) {
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  pad::benchmarks::DataVec tmp(state.range(0));
  pad::benchmarks::IndexVec tmpIdx(state.range(0));
  for (auto _ : state) {
    pad::tbb_presort::scatter(out.begin(), vec, index, tmp, tmpIdx);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbPresort)->Apply(pad::benchmarks::benchArgs)->UseRealTime();
BENCHMARK_MAIN();
