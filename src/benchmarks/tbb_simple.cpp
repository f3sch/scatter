#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialSimple(benchmark::State &state) {
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  std::vector<pad::benchmarks::DataType> out(state.range(0));
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
BENCHMARK_MAIN();
