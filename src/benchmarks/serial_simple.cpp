#include "scatter.h"
#include <array>
#include <benchmark/benchmark.h>
#include <chrono>
#include <numeric>
#include <tbb/parallel_for.h>
#include <vector>

static void benchArgs(benchmark::internal::Benchmark *b) {
  const auto lowerLimit = 1;
  const auto uppperLimit = 30;
  for (auto i = lowerLimit; i <= uppperLimit; ++i) {
    b->Args({1 << i});
  }
}

static void benchSerialSimple(benchmark::State &state) {
  // create array
  // create index array
  for (auto _ : state) {
    // something
    // benchmark::DoNotOptimize();
    benchmark::ClobberMemory();
  }
  // error checking
  // custom counters
}
BENCHMARK(benchSerialSimple)->Apply(benchArgs)->UseRealTime();
BENCHMARK_MAIN();
