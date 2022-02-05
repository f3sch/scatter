#ifndef BENCHMARKS
#define BENCHMARKS

#include <benchmark/benchmark.h>
#include <limits>
#include <vector>

#include <numeric>
#include <random>

#include <tbb/cache_aligned_allocator.h>

#include <range/v3/view/iota.hpp>
#include <range/v3/view/generate_n.hpp>


template <typename T, typename A = std::allocator<T>>
class default_init_allocator : public A
{
	// Implementation taken from https://stackoverflow.com/a/21028912.
	public:
		using A::A;

		template <typename U>
			struct rebind
			{
				using other = default_init_allocator<U, typename std::allocator_traits<A>::template rebind_alloc<U>>;
			};

		template <typename U>
			void
			construct(U* ptr)
			noexcept(std::is_nothrow_default_constructible<U>::value)
			{
				::new(static_cast<void*>(ptr)) U;
			}
		template <typename U, typename...ArgsT>
			void
			construct(U* ptr, ArgsT&&... args)
			{
				std::allocator_traits<A>::construct(static_cast<A&>(*this), ptr, std::forward<ArgsT>(args)...);
			}
};

struct linear_congruential_permutation_engine
{
  explicit linear_congruential_permutation_engine(size_t m, size_t seed)
      : m_x(seed)
      , m_mask(m - 1)
  {
    assert((m & (m - 1)) == 0); // assert m is a power of 2
  }

  size_t
  operator()()
  {
    m_x = (a * m_x + c) & m_mask; // & m_mask is the same as % m (if m is a power of 2)
    return m_x;
  }
  size_t min()
  { return 0u; }

  size_t max()
  { return m_mask; }

private:
    static constexpr size_t a = 16805;
    static constexpr size_t c = 9187;
    size_t m_x;
    size_t m_mask;
};

namespace pad::benchmarks
{
// Define data types
using DataType = float;
using Index = size_t;
template <typename T>
using Vec = std::vector<T, default_init_allocator<T, tbb::cache_aligned_allocator<T>> >;
using DataVec = std::vector<DataType, default_init_allocator<DataType, tbb::cache_aligned_allocator<DataType>> >;
using IndexVec = std::vector<Index, default_init_allocator<Index, tbb::cache_aligned_allocator<Index>> >;

template <typename DataType> inline auto distribution()
{
  if constexpr (std::is_floating_point<DataType>::value) {
    return std::uniform_real_distribution<>(
        std::numeric_limits<DataType>::min(),
        std::numeric_limits<DataType>::max());
  } else {
    return std::uniform_int_distribution<int>(std::numeric_limits<int>::min(),
                                              std::numeric_limits<int>::max());
  }
}

template <typename DataType = float, typename Index = size_t>
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

template <typename DataType = float, typename Index = size_t>
auto makeComputedInput(size_t n)
{
  auto vec = ranges::views::iota(0ul, n);
  auto index = ranges::views::generate_n(linear_congruential_permutation_engine { n, 461887 }, n);

  return std::make_pair(vec, index);
}

template <typename DataType = float, typename Index = size_t>
std::pair<Vec<DataType>, Vec<Index> >
makeChunkedPermutation(size_t n, size_t chunk_size = 1024, double prob = 1.0)
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


template <typename DataType = float, typename Index = size_t>
std::pair<Vec<DataType>, Vec<Index> > makeNormalDistributedShuffle(size_t n, size_t distance,
                                                    double prob = 1.0)
{
  Vec<DataType> vec(n);
  Vec<Index> index(n);
  std::random_device rnd_device;
  std::default_random_engine eng(rnd_device());
  std::mt19937 mersenne_engine{ rnd_device() };
  std::uniform_real_distribution<> dist(std::numeric_limits<DataType>::min(),
                                        std::numeric_limits<DataType>::max());
  std::normal_distribution<> shuffle_dist(0.0, distance);
  auto gen = [&dist, &eng]() { return dist(eng); };
  generate(begin(vec), end(vec), gen);
  std::iota(index.begin(), index.end(), 0);

  // shuffle data only in chunks, should more accuratley reflect
  // real situations, also some chunks can be skipped, adjust with prob
  for (size_t i = 0; i < n; ++i) {
    auto j = static_cast<size_t>((static_cast<std::ptrdiff_t>(shuffle_dist(mersenne_engine)) % n + n) % n);
    std::swap(index[i], index[j]);
  }

  return make_pair(vec, index);
}

bool cmpFloat(DataType a, DataType b,
              DataType eps = std::numeric_limits<DataType>::epsilon());
void verifyScatter(DataVec inVec, IndexVec index, DataVec out);
void benchArgs(benchmark::internal::Benchmark *b);
void benchLocalityArgs(benchmark::internal::Benchmark *b);
void benchGrainArgs(benchmark::internal::Benchmark *b);
void benchCounters(benchmark::State &state);
void benchGrainCounters(benchmark::State &state);
} // namespace pad::benchmarks

#endif
