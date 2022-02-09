#include "omp_serial.h"
#include "benchmarks.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchOmpSerial(benchmark::State &state)
{
  using namespace pad::benchmarks;
  auto N = state.range(0);
  auto [vec, index] = makeChunkedPermutation(state.range(0), 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::serial::scatter(out, vec, index);
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchCounters(state);
}
BENCHMARK(benchOmpSerial)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

BENCHMARK_MAIN();
