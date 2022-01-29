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

template <typename DataType> inline auto distribution()
{
  if constexpr (std::is_floating_point<DataType>::value) {
    return std::uniform_real_distribution<>(
        std::numeric_limits<DataType>::min(),
        std::numeric_limits<DataType>::max());
  } else {
    return std::uniform_int_distribution<>(
        std::numeric_limits<DataType>::min(),
        std::numeric_limits<DataType>::max());
  }
}

template <typename DataType = double, typename Index = size_t>
std::pair<Vec<DataType>, Vec<Index> > makeData(size_t n)
{
  Vec<DataType> vec(n);
  Vec<Index> index(n);
  std::random_device rnd_device;
  std::default_random_engine eng(rnd_device());
  std::mt19937 mersenne_engine{ rnd_device() };
  auto dist = distribution<DataType>();
  auto gen = [&dist, &eng]() { return dist(eng); };
  generate(begin(vec), end(vec), gen);
  std::iota(index.begin(), index.end(), 0);
  shuffle(begin(index), end(index), mersenne_engine);

  return make_pair(vec, index);
}

template <typename DataType = double, typename Index = size_t>
std::pair<Vec<DataType>, Vec<Index> > makeDataLocal(size_t n, size_t chunk_size,
                                                    double prob = 1.0)
{
  Vec<DataType> vec(n);
  Vec<Index> index(n);
  std::random_device rnd_device;
  std::default_random_engine eng(rnd_device());
  std::mt19937 mersenne_engine{ rnd_device() };
  std::uniform_real_distribution<> dist(std::numeric_limits<DataType>::min(),
                                        std::numeric_limits<DataType>::max());
  std::uniform_real_distribution<> shuffle_dist(0.0, 1.0);
  auto gen = [&dist, &eng]() { return dist(eng); };
  generate(begin(vec), end(vec), gen);
  std::iota(index.begin(), index.end(), 0);

  // shuffle data only in chunks, should more accuratley reflect
  // real situations, also some chunks can be skipped, adjust with prob
  auto steps = (n >= chunk_size) ? n / chunk_size : 1;
  for (decltype(steps) i = 0; i <= steps; ++i) {
    if (shuffle_dist(mersenne_engine) > prob)
      continue;
    auto it = begin(index) + i * chunk_size;
    auto jt = begin(index) + (i + 1) * chunk_size;
    if (index.size() < (i + 1) * chunk_size)
      jt = end(index);
    shuffle(it, jt, mersenne_engine);
  }

  return make_pair(vec, index);
}

bool cmpFloat(DataType a, DataType b,
              DataType eps = std::numeric_limits<DataType>::epsilon());
void verifyScatter(DataVec inVec, IndexVec index, DataVec out);
void benchArgs(benchmark::internal::Benchmark *b);
void benchCounters(benchmark::State &state);
} // namespace pad::benchmarks

#endif
