#ifndef BENCHMARKS
#define BENCHMARKS

#include <benchmark/benchmark.h>
#include <limits>
#include <vector>

#include <tbb/cache_aligned_allocator.h>

namespace pad::benchmarks {
// Define data types
using DataType = double;
using Index = size_t;
using DataVec = std::vector<DataType, tbb::cache_aligned_allocator<DataType>>;
using IndexVec = std::vector<Index, tbb::cache_aligned_allocator<Index>>;

std::pair<DataVec, IndexVec> makeData(Index n);
bool cmpFloat(DataType a, DataType b,
              DataType eps = std::numeric_limits<DataType>::epsilon());
void verifyScatter(DataVec inVec, IndexVec index,
                   DataVec out);
void benchArgs(benchmark::internal::Benchmark *b);
void benchCounters(benchmark::State &state);
} // namespace pad::benchmarks

#endif
