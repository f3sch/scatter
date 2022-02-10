#include "omp_parallel.h"
#include "benchmarks.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchOmpParallelStatic(benchmark::State &state)
{
  using namespace pad::benchmarks;
  auto N = state.range(0);
  auto [vec, index] = makeChunkedPermutation(state.range(0), 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, omp_sched_static,
                                state.range(1));
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelStatic)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchOmpParallelAuto(benchmark::State &state)
{
  using namespace pad::benchmarks;
  auto N = state.range(0);
  auto [vec, index] = makeChunkedPermutation(state.range(0), 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, omp_sched_auto,
                                state.range(1));
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelAuto)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchOmpParallelDynamic(benchmark::State &state)
{
  using namespace pad::benchmarks;
  auto N = state.range(0);
  auto [vec, index] = makeChunkedPermutation(state.range(0), 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, omp_sched_dynamic,
                                state.range(1));
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelDynamic)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchOmpParallelGuided(benchmark::State &state)
{
  using namespace pad::benchmarks;
  auto N = state.range(0);
  auto [vec, index] = makeChunkedPermutation(state.range(0), 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, omp_sched_guided,
                                state.range(1));
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelGuided)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchOmpParallelMonotonic(benchmark::State &state)
{
  using namespace pad::benchmarks;
  auto N = state.range(0);
  auto [vec, index] = makeChunkedPermutation(state.range(0), 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, omp_sched_monotonic,
                                state.range(1));
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelMonotonic)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

BENCHMARK_MAIN();
