#include "benchmarks.h"
#include "tbb_binning.h"
#include <benchmark/benchmark.h>
#include <vector>

static void benchTbbBinningFullyAssociativeId(benchmark::State &state)
{
  auto N = state.range(0);
  pad::benchmarks::DataVec vec(N);
  pad::benchmarks::IndexVec index(N);
  pad::benchmarks::DataVec out(N);

  std::iota(vec.begin(), vec.end(), 0);
  std::iota(index.begin(), index.end(), 0);

  for (auto _ : state) {
    pad::tbb_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningFullyAssociativeId)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchTbbBinningFullyAssociativeRandom(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningFullyAssociativeRandom)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchTbbBinningFullyAssociativeChunkedPermutation(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeChunkedPermutation(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningFullyAssociativeChunkedPermutation)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchTbbBinningFullyAssociativeNormalDistributedShuffle(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::fully_associative::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningFullyAssociativeNormalDistributedShuffle)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchTbbBinningFullyAssociativeNormalDistributedShuffle2(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::fully_associative::scatter<16384, 1024>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningFullyAssociativeNormalDistributedShuffle2)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchTbbBinningDirectMappingId(benchmark::State &state)
{
  auto N = state.range(0);
  pad::benchmarks::DataVec vec(N);
  pad::benchmarks::IndexVec index(N);
  pad::benchmarks::DataVec out(N);

  std::iota(vec.begin(), vec.end(), 0);
  std::iota(index.begin(), index.end(), 0);

  for (auto _ : state) {
    pad::tbb_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}

BENCHMARK(benchTbbBinningDirectMappingId)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchTbbBinningDirectMappingRandom(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeData(state.range(0));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningDirectMappingRandom)
    ->Apply(pad::benchmarks::benchArgs)
    ->UseRealTime();

static void benchTbbBinningDirectMappingChunkedPermutation(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeChunkedPermutation(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningDirectMappingChunkedPermutation)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchTbbBinningDirectMappingNormalDistributedShuffle(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::direct_mapping::scatter(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningDirectMappingNormalDistributedShuffle)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchTbbBinningDirectMappingNormalDistributedShuffle2(benchmark::State &state) {
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::direct_mapping::scatter<16384, 1024, 1024, 8>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningDirectMappingNormalDistributedShuffle2)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchTbbBinningDirectMappingNormalDistributedShuffle3(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::direct_mapping::scatter<16384, 1024, 64, 64>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningDirectMappingNormalDistributedShuffle3)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

static void benchTbbBinningDirectMappingNormalDistributedShuffle4(benchmark::State &state)
{
  auto [vec, index] = pad::benchmarks::makeNormalDistributedShuffle(state.range(0), state.range(1));
  pad::benchmarks::DataVec out(state.range(0));
  for (auto _ : state) {
    pad::tbb_binning::direct_mapping::scatter<16384, 1024, 1024, 64>(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  pad::benchmarks::verifyScatter(vec, index, out);
  pad::benchmarks::benchCounters(state);
}
BENCHMARK(benchTbbBinningDirectMappingNormalDistributedShuffle4)->Apply(pad::benchmarks::benchLocalityArgs)->UseRealTime();

BENCHMARK_MAIN();
