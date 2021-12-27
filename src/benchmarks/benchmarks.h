#ifndef BENCHMARKS
#define BENCHMARKS

#include <benchmark/benchmark.h>
#include <limits>
#include <vector>

namespace pad::benchmarks {
// Define data types
using DataType = double;
using Index = unsigned int;

std::pair<std::vector<DataType>, std::vector<Index>> makeData(Index n);
bool cmpFloat(DataType a, DataType b,
              DataType eps = std::numeric_limits<DataType>::epsilon());
void verifyScatter(std::vector<DataType> inVec, std::vector<Index> index,
                   std::vector<DataType> out);
void benchArgs(benchmark::internal::Benchmark *b);
void benchCounters(benchmark::State &state);
} // namespace pad::benchmarks

#endif
