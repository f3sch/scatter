#ifndef BENCHMARKS
#define BENCHMARKS

#include <benchmark/benchmark.h>
#include <limits>
#include <vector>

#include <numeric>
#include <random>

#include <tbb/cache_aligned_allocator.h>

namespace pad::benchmarks
{
// Define data types
using DataType = double;
using Index = size_t;
template <typename T>
using Vec = std::vector<T, tbb::cache_aligned_allocator<T> >;
using DataVec = std::vector<DataType, tbb::cache_aligned_allocator<DataType> >;
using IndexVec = std::vector<Index, tbb::cache_aligned_allocator<Index> >;

template <typename DataType = double, typename Index = size_t>
std::pair<Vec<DataType>, Vec<Index> > makeData(size_t n)
{
  Vec<DataType> vec(n);
  Vec<Index> index(n);
  std::random_device rnd_device;
  std::default_random_engine eng(rnd_device());
  std::mt19937 mersenne_engine{ rnd_device() };
  std::uniform_real_distribution<> dist(std::numeric_limits<DataType>::min(),
                                        std::numeric_limits<DataType>::max());
  auto gen = [&dist, &eng]() { return dist(eng); };
  generate(begin(vec), end(vec), gen);
  std::iota(index.begin(), index.end(), 0);
  shuffle(begin(index), end(index), mersenne_engine);

  return make_pair(vec, index);
}

std::pair<std::vector<DataType>, std::vector<Index> > bool
cmpFloat(DataType a, DataType b,
         DataType eps = std::numeric_limits<DataType>::epsilon());
void verifyScatter(DataVec inVec, IndexVec index, DataVec out);
void benchArgs(benchmark::internal::Benchmark *b);
void benchCounters(benchmark::State &state);
} // namespace pad::benchmarks

#endif
