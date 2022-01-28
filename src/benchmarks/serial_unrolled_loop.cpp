#include "benchmarks.h"
#include "serial_unrolled_loop.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialUnrolledLoopRandom(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_unrolled_loop::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialUnrolledLoopRandom)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();
BENCHMARK_MAIN();
