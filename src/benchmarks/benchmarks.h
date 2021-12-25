#ifndef BENCHMARKS
#define BENCHMARKS

#include <benchmark/benchmark.h>
#include <limits>
#include <vector>

std::pair<std::vector<float>, std::vector<unsigned int>>
makeData(unsigned int n);
bool cmpFloat(float a, float b,
              float eps = std::numeric_limits<float>::epsilon());
void verifyScatter(std::vector<float> inVec, std::vector<unsigned int> index,
                   std::vector<float> out);
void benchArgs(benchmark::internal::Benchmark *b);
void benchCounters(benchmark::State &state);

#endif
