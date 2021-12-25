#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchStdSimple(benchmark::State &state) {
  auto [vec, index] = makeData(state.range(0));
  std::vector<DataType> out(state.range(0));
  for (auto _ : state) {
    pad::serial::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchCounters(state);
}
BENCHMARK(benchStdSimple)->Apply(benchArgs)->UseRealTime();
BENCHMARK_MAIN();
