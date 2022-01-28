#include "benchmarks.h"
#include "serial_simd.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialSimdId(benchmark::State &state) {
	auto N = state.range(0);
  pad::benchmarks::DataVec vec(N);
  pad::benchmarks::IndexVec index(N);
  pad::benchmarks::DataVec out(N);

	std::iota(vec.begin(), vec.end(), 0);
	std::iota(index.begin(), index.end(), 0);
	for (auto _ : state) {
		pad::serial_simd::scatter(out.begin(), vec, index);
		benchmark::DoNotOptimize(vec.data());
		benchmark::DoNotOptimize(index.data());
		benchmark::ClobberMemory();
	}
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimdId)->Apply(pad::benchmarks::benchArgs)->UseRealTime();

static void benchSerialSimdRandom(benchmark::State &state) {
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_simd::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialSimdRandom)->Apply(pad::benchmarks::benchArgs)->UseRealTime();
BENCHMARK_MAIN();
