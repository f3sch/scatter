#include "benchmarks.h"
#include "serial_unrolled_loop.h"
#include <benchmark/benchmark.h>
#include <vector>

//static void benchSerialUnrolledLoopId(benchmark::State &state) {
//	auto N = state.range(0);
//	DataVec vec(N);
//	IndexVec index(N);
//	DataVec out(N);
//
//	std::iota(vec.begin(), vec.end(), 0);
//	std::iota(index.begin(), index.end(), 0);
//	for (auto _ : state) {
//		pad::serial_simd::scatter(out.begin(), vec, index);
//		benchmark::DoNotOptimize(vec.data());
//		benchmark::DoNotOptimize(index.data());
//		benchmark::ClobberMemory();
//	}
//	// verifyScatter(vec, index, out);
//	benchCounters(state);
//}
//BENCHMARK(benchSerialSimdId)->Apply(benchArgs)->UseRealTime();


static void benchSerialUnrolledLoopRandom(benchmark::State &state) {
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  std::vector<pad::benchmarks::DataType> out(state.range(0));
  for (auto _ : state) {
    pad::serial_unrolled_loop::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialUnrolledLoopRandom)->Apply(pad::benchmarks::benchArgs)->UseRealTime();
BENCHMARK_MAIN();
