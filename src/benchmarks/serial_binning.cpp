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


static void benchSerialBinningFACompRand(benchmark::State &state)
{
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    auto [vec, index] = pad::benchmarks::makeComputedInput(state.range(0));
    pad::serial_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningFACompRand)->Apply(pad::benchmarks::benchArgs)->UseRealTime();


static void benchSerialBinningFullyAssociativeChunkedPermutation(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeChunkedPermutation(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningFullyAssociativeChunkedPermutation)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningFullyAssociativeNormalDistributedShuffle(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningFullyAssociativeNormalDistributedShuffle)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningFullyAssociativeNormalDistributedShuffle2(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningFullyAssociativeNormalDistributedShuffle2)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

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


static void benchSerialBinningDMCompRand(benchmark::State &state)
{
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    auto [vec, index] = pad::benchmarks::makeComputedInput(state.range(0));
    pad::serial_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchSerialBinningDMCompRand)->Apply(pad::benchmarks::benchArgs)->UseRealTime();


static void benchSerialBinningDirectMappingChunkedPermutation(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeChunkedPermutation(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningDirectMappingChunkedPermutation)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingNormalDistributedShuffle(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningDirectMappingNormalDistributedShuffle)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingNormalDistributedShuffle2(benchmark::State &state) {
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningDirectMappingNormalDistributedShuffle2)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingNormalDistributedShuffle3(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningDirectMappingNormalDistributedShuffle3)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchSerialBinningDirectMappingNormalDistributedShuffle4(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
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
BENCHMARK(benchSerialBinningDirectMappingNormalDistributedShuffle4)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

BENCHMARK_MAIN();
