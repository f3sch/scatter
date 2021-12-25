#include "benchmarks.h"
#include "scatter.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialSimple(benchmark::State &state) {
  auto [vec, index] = makeData(state.range(0));
  std::vector<DataType> out(state.range(0));
  for (auto _ : state) {
    pad::tbb::scatter_simple(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchCounters(state);
}
BENCHMARK(benchSerialSimple)->Apply(benchArgs)->UseRealTime();
BENCHMARK_MAIN();
