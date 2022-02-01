#include "benchmarks.h"
#include "serial_binning.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchSerialBinningFullyAssociativeId(benchmark::State &state)
{
  auto N = state.range(0);
  pad::benchmarks::DataVec vec(N);
  pad::benchmarks::IndexVec index(N);
  pad::benchmarks::DataVec out(N);

  std::iota(vec.begin(), vec.end(), 0);
  std::iota(index.begin(), index.end(), 0);

  for (auto _ : state) {
    pad::serial_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningFullyAssociativeId)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchSerialBinningFullyAssociativeRandom(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningFullyAssociativeRandom)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchSerialBinningFullyAssociativeLocal(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningFullyAssociativeLocal)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningFullyAssociativeLocal2(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::fully_associative::scatter<16384, 1024>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningFullyAssociativeLocal2)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingId(benchmark::State &state)
{
  auto N = state.range(0);
  pad::benchmarks::DataVec vec(N);
  pad::benchmarks::IndexVec index(N);
  pad::benchmarks::DataVec out(N);

  std::iota(vec.begin(), vec.end(), 0);
  std::iota(index.begin(), index.end(), 0);

  for (auto _ : state) {
    pad::serial_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}

BENCHMARK(benchSerialBinningDirectMappingId)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchSerialBinningDirectMappingRandom(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningDirectMappingRandom)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchSerialBinningDirectMappingLocal(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningDirectMappingLocal)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingLocal2(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::direct_mapping::scatter<16384, 1024, 1024, 8>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningDirectMappingLocal2)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingLocal3(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::direct_mapping::scatter<16384, 1024, 64, 64>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningDirectMappingLocal3)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingLocal4(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeDataLocal(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::serial_binning::direct_mapping::scatter<16384, 1024, 1024, 64>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningDirectMappingLocal4)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

BENCHMARK_MAIN();
