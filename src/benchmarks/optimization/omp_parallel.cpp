#include "omp_parallel.h"
#include "benchmarks.h"
#include <benchmark/benchmark.h>
#include <vector>

using namespace pad::benchmarks;

static void benchOmpParallelStatic(benchmark::State &state)
{
  auto N = state.range(0); // Problem size
  auto ChunkSize = state.range(1); // Chunksize
  auto nThreads = state.range(2); // #Threads

  auto [vec, index] = makeChunkedPermutation(N, 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, nThreads, omp_sched_static,
                                ChunkSize);

    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelStatic)->Apply(benchOmpArgs)->UseRealTime();

static void benchOmpParallelMonotonic(benchmark::State &state)
{
  auto N = state.range(0); // Problem size
  auto ChunkSize = state.range(1); // Chunksize
  auto nThreads = state.range(2); // #Threads

  auto [vec, index] = makeChunkedPermutation(N, 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, nThreads, omp_sched_monotonic,
                                ChunkSize);

    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelMonotonic)->Apply(benchOmpArgs)->UseRealTime();

static void benchOmpParallelAuto(benchmark::State &state)
{
  auto N = state.range(0); // Problem size
  auto ChunkSize = state.range(1); // Chunksize
  auto nThreads = state.range(2); // #Threads

  auto [vec, index] = makeChunkedPermutation(N, 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, nThreads, omp_sched_auto,
                                ChunkSize);

    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelAuto)->Apply(benchOmpArgs)->UseRealTime();

static void benchOmpParallelGuided(benchmark::State &state)
{
  auto N = state.range(0); // Problem size
  auto ChunkSize = state.range(1); // Chunksize
  auto nThreads = state.range(2); // #Threads

  auto [vec, index] = makeChunkedPermutation(N, 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, nThreads, omp_sched_guided,
                                ChunkSize);

    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelGuided)->Apply(benchOmpArgs)->UseRealTime();

static void benchOmpParallelDynamic(benchmark::State &state)
{
  auto N = state.range(0); // Problem size
  auto ChunkSize = state.range(1); // Chunksize
  auto nThreads = state.range(2); // #Threads

  auto [vec, index] = makeChunkedPermutation(N, 16);
  DataVec out(N);
  for (auto _ : state) {
    pad::omp::parallel::scatter(out, vec, index, nThreads, omp_sched_dynamic,
                                ChunkSize);

    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchOmpCounters(state);
}
BENCHMARK(benchOmpParallelDynamic)->Apply(benchOmpArgs)->UseRealTime();

BENCHMARK_MAIN();
