#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSTLSimple(benchmark::State &state) {
  auto [vec, index] = makeData(state.range(0));
  std::vector<DataType> out(state.range(0));
  for (auto _ : state) {
    pad::stl::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchCounters(state);
}
BENCHMARK(benchSTLSimple)->Apply(benchArgs)->UseRealTime();
BENCHMARK_MAIN();
