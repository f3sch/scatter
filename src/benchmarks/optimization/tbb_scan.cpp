#include "benchmarks.h"
#include "scatter.h"
#include <oneapi/tbb.h>
#include <benchmark/benchmark.h>
#include <vector>

#define SIZE 1 << 27

static void benchTBBScanPartition(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(SIZE);
  pad::benchmarks::DataVec out(SIZE);
  for (auto _ : state) {
    pad::tbb::scan::scatter(out.begin(), vec, index, state.range(0));
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchGrainCounters(state);
}
BENCHMARK(benchTBBScanPartition)
    ->Iterations(10)
    ->Apply(pad::benchmarks::benchPartitionArgs)
    ->UseRealTime();

BENCHMARK_MAIN();
