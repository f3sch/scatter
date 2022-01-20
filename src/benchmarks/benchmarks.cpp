#include "benchmarks.h"
#include "scatter.h"
#include <algorithm>
#include <array>
#include <benchmark/benchmark.h>
#include <chrono>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

namespace pad::benchmarks
{
using namespace std;

pair<vector<DataType>, vector<Index> > makeData(Index n)
{
  vector<DataType> vec(n);
  vector<Index> index(n);
  random_device rnd_device;
  default_random_engine eng(rnd_device());
  mt19937 mersenne_engine{ rnd_device() };
  uniform_real_distribution<> dist(numeric_limits<DataType>::min(),
                                   numeric_limits<DataType>::max());
  auto gen = [&dist, &eng]() { return dist(eng); };
  generate(begin(vec), end(vec), gen);
  std::iota(index.begin(), index.end(), 0);
  shuffle(begin(index), end(index), mersenne_engine);

  return make_pair(vec, index);
}

bool cmpFloat(DataType a, DataType b, DataType eps)
{
  return fabs(a - b) <= eps;
}

void verifyScatter(vector<DataType> inVec, vector<Index> index,
                   vector<DataType> out)
{
  vector<DataType> correct(inVec.size());
  pad::serial::scatter(correct.begin(), inVec, index);
  for (Index i = 0; i < inVec.size(); i++) {
    if (!cmpFloat(out[i], correct[i])) {
      throw runtime_error("Wrong Results");
    }
  }
}

void benchArgs(benchmark::internal::Benchmark *b)
{
  const auto lowerLimit = 15;
  const auto uppperLimit = 30;
  for (auto i = lowerLimit; i <= uppperLimit; ++i) {
    b->Args({ 1 << i });
  }
}

void benchCounters(benchmark::State &state)
{
  state.counters["Elements"] = state.range(0);
  auto GOPS = int64_t(state.iterations()) * int64_t(state.range(0));
  state.counters["GOPS"] = GOPS;
  state.counters["GOPSperIter"] = GOPS / state.iterations();
  state.counters["Bytes_processed"] =
      2 * state.range(0) * sizeof(DataType) + sizeof(unsigned int);
}

} // namespace pad::benchmarks
