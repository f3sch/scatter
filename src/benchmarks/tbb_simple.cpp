#include "scatter.h"
#include <algorithm>
#include <array>
#include <benchmark/benchmark.h>
#include <chrono>
#include <limits>
#include <numeric>
#include <random>
#include <tbb/parallel_for.h>
#include <vector>

using namespace std;

static pair<vector<float>, vector<unsigned int>> makeData(unsigned int n) {
  vector<float> vec(n);
  vector<unsigned int> index(n);
  random_device rnd_device;
  default_random_engine eng(rnd_device());
  mt19937 mersenne_engine{rnd_device()};
  uniform_real_distribution<> dist(numeric_limits<float>::min(),
                                   numeric_limits<float>::max());
  auto gen = [&dist, &eng]() { return dist(eng); };
  generate(begin(vec), end(vec), gen);
  for (unsigned int i = 0; i < n; i++)
    index[i] = i;
  shuffle(begin(index), end(index), mersenne_engine);

  return make_pair(vec, index);
}

bool cmpFloat(float a, float b, float eps = numeric_limits<float>::epsilon()) {
  return fabs(a - b) <= eps;
}

static void verifyScatter(vector<float> inVec, vector<unsigned int> index,
                          vector<float> out) {
  vector<float> correct(inVec.size());
  pad::serial_scatter(correct.begin(), inVec, index);
  for (unsigned int i = 0; i < inVec.size(); i++) {
    if (!cmpFloat(out[i], correct[i])) {
      throw runtime_error("Wrong Results");
    }
  }
}

static void benchArgs(benchmark::internal::Benchmark *b) {
  const auto lowerLimit = 15;
  const auto uppperLimit = 30;
  for (auto i = lowerLimit; i <= uppperLimit; ++i) {
    b->Args({1 << i});
  }
}

static void benchCounters(benchmark::State &state) {
  state.counters["Elements"] = state.range(0);
  auto GOPS = int64_t(state.iterations()) * int64_t(state.range(0));
  state.counters["GOPS"] = GOPS;
  state.counters["GOPSperIter"] = GOPS / state.iterations();
  state.counters["Bytes_processed"] =
      2 * state.range(0) * sizeof(float) + sizeof(unsigned int);
}

static void benchSerialSimple(benchmark::State &state) {
  auto [vec, index] = makeData(state.range(0));
  vector<float> out(state.range(0));
  for (auto _ : state) {
    pad::tbb_scatter_simple(out.begin(), vec, index);
    benchmark::DoNotOptimize(vec.data());
    benchmark::DoNotOptimize(index.data());
    benchmark::ClobberMemory();
  }
  verifyScatter(vec, index, out);
  benchCounters(state);
}
BENCHMARK(benchSerialSimple)->Apply(benchArgs)->UseRealTime();
BENCHMARK_MAIN();
