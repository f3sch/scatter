#include "benchmarks.h"
#include "scatter.h"
#include <oneapi/tbb.h>
#include <benchmark/benchmark.h>
#include <vector>

#define SIZE 1 << 30

static void benchTBBSimpleGrainAuto(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(SIZE);
  pad::benchmarks::DataVec out(SIZE);
  for (auto _ : state) {
    pad::tbb_simple::scatter(out.begin(), vec, index, state.range(0),
                             tbb::auto_partitioner());
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchGrainCounters(state);
}
BENCHMARK(benchTBBSimpleGrainAuto)
    ->Apply(pad::benchmarks::benchGrainArgs)
    ->UseRealTime();

static void benchTBBSimpleGrainSimple(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(SIZE);
  pad::benchmarks::DataVec out(SIZE);
  for (auto _ : state) {
    pad::tbb_simple::scatter(out.begin(), vec, index, state.range(0),
                             tbb::simple_partitioner());
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchGrainCounters(state);
}
BENCHMARK(benchTBBSimpleGrainSimple)
    ->Apply(pad::benchmarks::benchGrainArgs)
    ->UseRealTime();

static void benchTBBSimpleGrainAffinity(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(SIZE);
  pad::benchmarks::DataVec out(SIZE);
  for (auto _ : state) {
    pad::tbb_simple::scatter(out.begin(), vec, index, state.range(0),
                             tbb::affinity_partitioner());
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchGrainCounters(state);
}
BENCHMARK(benchTBBSimpleGrainAffinity)
    ->Apply(pad::benchmarks::benchGrainArgs)
    ->UseRealTime();

static void benchTBBSimpleGrainStatic(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(SIZE);
  pad::benchmarks::DataVec out(SIZE);
  for (auto _ : state) {
    pad::tbb_simple::scatter(out.begin(), vec, index, state.range(0),
                             tbb::static_partitioner());
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchGrainCounters(state);
}
BENCHMARK(benchTBBSimpleGrainStatic)
    ->Apply(pad::benchmarks::benchGrainArgs)
    ->UseRealTime();

BENCHMARK_MAIN();
