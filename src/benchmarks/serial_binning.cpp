#include "benchmarks.h"
#include "serial_binning.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialBinning(benchmark::State &state) {
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinning)->Apply(pad::benchmarks::benchArgs)->UseRealTime();
BENCHMARK_MAIN();
