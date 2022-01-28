//
// Created by anton on 1/20/22.
//

#ifndef SERIAL_BINNING_H
#define SERIAL_BINNING_H

#include <cassert>
#include <iterator>
#include <range/v3/size.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/take_exactly.hpp>
#include <range/v3/algorithm/fill.hpp>
#include <span>
#include <random>

namespace pad::serial_binning
{

namespace detail
{
inline constexpr size_t log2(size_t x)
{
  return __builtin_ctz(x);
}
} // namespace detail

namespace fully_associative
{
template <size_t chunkSize = 1024, size_t binSize = 64, typename OutIt_t,
          typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng)
{
  using namespace ranges;
  using namespace ranges::views;
  using Idx_t = std::ranges::range_value_t<IdxRng_t>;
  using Val_t = std::ranges::range_value_t<InRng_t>;

  struct KeyValPair {
    Idx_t idx;
    Val_t val;
  };

  auto flush = [&](auto &&bin) {
    for (auto &[idx, val] : bin) {
      outIt[idx] = val;
    }
  };

  static constexpr Idx_t empty_tag = std::numeric_limits<Idx_t>::max();
  static constexpr auto logBinSize = detail::log2(binSize);
  auto valChunks = chunk(inRng, chunkSize);
  auto idxChunks = chunk(idxRng, chunkSize);
  auto bin0 = std::array<KeyValPair, binSize>{};
  auto bin1 = std::array<KeyValPair, binSize>{};
  auto bin2 = std::array<KeyValPair, binSize>{};
  auto bin3 = std::array<KeyValPair, binSize>{};
  auto bin4 = std::array<KeyValPair, binSize>{};
  auto bin5 = std::array<KeyValPair, binSize>{};
  auto bin6 = std::array<KeyValPair, binSize>{};
  auto bin7 = std::array<KeyValPair, binSize>{};
  Idx_t bin0Tag = empty_tag;
  Idx_t bin1Tag = empty_tag;
  Idx_t bin2Tag = empty_tag;
  Idx_t bin3Tag = empty_tag;
  Idx_t bin4Tag = empty_tag;
  Idx_t bin5Tag = empty_tag;
  Idx_t bin6Tag = empty_tag;
  Idx_t bin7Tag = empty_tag;
  uint_fast8_t bin0FillLevel = 0;
  uint_fast8_t bin1FillLevel = 0;
  uint_fast8_t bin2FillLevel = 0;
  uint_fast8_t bin3FillLevel = 0;
  uint_fast8_t bin4FillLevel = 0;
  uint_fast8_t bin5FillLevel = 0;
  uint_fast8_t bin6FillLevel = 0;
  uint_fast8_t bin7FillLevel = 0;

  std::uniform_int_distribution dist{ 0, 7 };
  std::mt19937 random_engine{ std::random_device{}() };

  for (auto &&[valChunk, idxChunk] : zip(valChunks, idxChunks)) {
    for (auto &&[val, idx] : zip(valChunk, idxChunk)) {
      assert(0 <= idx && static_cast<size_t>(idx) < ranges::size(idxRng));
      auto tag = idx >> logBinSize;
      if (tag == bin0Tag) {
        bin0[bin0FillLevel] = { idx, val };
        ++bin0FillLevel;

        if (bin0FillLevel == binSize) {
          flush(bin0);
          bin0FillLevel = 0;
          bin0Tag = empty_tag;
        }
      } else if (tag == bin1Tag) {
        bin1[bin1FillLevel] = { idx, val };
        ++bin1FillLevel;

        if (bin1FillLevel == binSize) {
          flush(bin1);
          bin1FillLevel = 1;
          bin1Tag = empty_tag;
        }
      } else if (tag == bin2Tag) {
        bin2[bin2FillLevel] = { idx, val };
        ++bin2FillLevel;

        if (bin2FillLevel == binSize) {
          flush(bin2);
          bin2FillLevel = 2;
          bin2Tag = empty_tag;
        }
      } else if (tag == bin3Tag) {
        bin3[bin3FillLevel] = { idx, val };
        ++bin3FillLevel;

        if (bin3FillLevel == binSize) {
          flush(bin3);
          bin3FillLevel = 3;
          bin3Tag = empty_tag;
        }
      } else if (tag == bin4Tag) {
        bin4[bin4FillLevel] = { idx, val };
        ++bin4FillLevel;

        if (bin4FillLevel == binSize) {
          flush(bin4);
          bin4FillLevel = 4;
          bin4Tag = empty_tag;
        }
      } else if (tag == bin5Tag) {
        bin5[bin5FillLevel] = { idx, val };
        ++bin5FillLevel;

        if (bin5FillLevel == binSize) {
          flush(bin5);
          bin5FillLevel = 5;
          bin5Tag = empty_tag;
        }
      } else if (tag == bin6Tag) {
        bin6[bin6FillLevel] = { idx, val };
        ++bin6FillLevel;

        if (bin6FillLevel == binSize) {
          flush(bin6);
          bin6FillLevel = 6;
          bin6Tag = empty_tag;
        }
      } else if (tag == bin7Tag) {
        bin7[bin7FillLevel] = { idx, val };
        ++bin7FillLevel;

        if (bin7FillLevel == binSize) {
          flush(bin7);
          bin7FillLevel = 7;
          bin7Tag = empty_tag;
        }
      } else {
        if (bin0FillLevel == 0) {
          bin0[0] = { idx, val };
          bin0Tag = tag;
          bin0FillLevel = 1;
        } else if (bin1FillLevel == 0) {
          bin1[0] = { idx, val };
          bin1Tag = tag;
          bin1FillLevel = 1;
        } else if (bin2FillLevel == 0) {
          bin2[0] = { idx, val };
          bin2Tag = tag;
          bin2FillLevel = 1;
        } else if (bin3FillLevel == 0) {
          bin3[0] = { idx, val };
          bin3Tag = tag;
          bin3FillLevel = 1;
        } else if (bin4FillLevel == 0) {
          bin4[0] = { idx, val };
          bin4Tag = tag;
          bin4FillLevel = 1;
        } else if (bin5FillLevel == 0) {
          bin5[0] = { idx, val };
          bin5Tag = tag;
          bin5FillLevel = 1;
        } else if (bin6FillLevel == 0) {
          bin6[0] = { idx, val };
          bin6Tag = tag;
          bin6FillLevel = 1;
        } else if (bin7FillLevel == 0) {
          bin7[0] = { idx, val };
          bin7Tag = tag;
          bin7FillLevel = 1;
        } else {
          auto randomBin = dist(random_engine);
          if (randomBin == 0) {
            flush(ranges::views::take_exactly(bin0, bin0FillLevel));
            bin0[0] = { idx, val };
            bin0Tag = tag;
            bin0FillLevel = 1;
          } else if (randomBin == 1) {
            flush(ranges::views::take_exactly(bin1, bin1FillLevel));
            bin1[0] = { idx, val };
            bin1Tag = tag;
            bin1FillLevel = 1;
          } else if (randomBin == 2) {
            flush(ranges::views::take_exactly(bin2, bin2FillLevel));
            bin2[0] = { idx, val };
            bin2Tag = tag;
            bin2FillLevel = 1;
          } else if (randomBin == 3) {
            flush(ranges::views::take_exactly(bin3, bin3FillLevel));
            bin3[0] = { idx, val };
            bin3Tag = tag;
            bin3FillLevel = 1;
          } else if (randomBin == 4) {
            flush(ranges::views::take_exactly(bin4, bin4FillLevel));
            bin4[0] = { idx, val };
            bin4Tag = tag;
            bin4FillLevel = 1;
          } else if (randomBin == 5) {
            flush(ranges::views::take_exactly(bin5, bin5FillLevel));
            bin5[0] = { idx, val };
            bin5Tag = tag;
            bin5FillLevel = 1;
          } else if (randomBin == 6) {
            flush(ranges::views::take_exactly(bin6, bin6FillLevel));
            bin6[0] = { idx, val };
            bin6Tag = tag;
            bin6FillLevel = 1;
          } else if (randomBin == 7) {
            flush(ranges::views::take_exactly(bin7, bin7FillLevel));
            bin7[0] = { idx, val };
            bin7Tag = tag;
            bin7FillLevel = 1;
          }
        }
      }
    }

    flush(ranges::views::take_exactly(bin0, bin0FillLevel));
    flush(ranges::views::take_exactly(bin1, bin1FillLevel));
    flush(ranges::views::take_exactly(bin2, bin2FillLevel));
    flush(ranges::views::take_exactly(bin3, bin3FillLevel));
    flush(ranges::views::take_exactly(bin4, bin4FillLevel));
    flush(ranges::views::take_exactly(bin5, bin5FillLevel));
    flush(ranges::views::take_exactly(bin6, bin6FillLevel));
    flush(ranges::views::take_exactly(bin7, bin7FillLevel));
    bin0FillLevel = 0;
    bin1FillLevel = 0;
    bin2FillLevel = 0;
    bin3FillLevel = 0;
    bin4FillLevel = 0;
    bin5FillLevel = 0;
    bin6FillLevel = 0;
    bin7FillLevel = 0;
  }
}

} // namespace fully_associative

namespace direct_mapping
{
template <size_t chunkSize = 1024, size_t binSize = 64,
          size_t cacheLineSize = 64, size_t bankCount = 8, typename OutIt_t,
          typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng)
{
  using namespace ranges;
  using namespace ranges::views;
  using Idx_t = std::ranges::range_value_t<IdxRng_t>;
  using Val_t = std::ranges::range_value_t<InRng_t>;

  auto flush = [&](auto &&idxArray, auto &&valArray, size_t count) {
    for (size_t i = 0; i < count; ++i) {
      outIt[idxArray[i]] = valArray[i];
    }
  };

  static constexpr auto logBinSize = pad::serial_binning::detail::log2(binSize);
  static constexpr auto bankMask =
      bankCount - 1; // e.g. 8 - 1 == 7 == 0b00000111
  auto valChunks = chunk(inRng, chunkSize);
  auto idxChunks = chunk(idxRng, chunkSize);

  for (auto &&[valChunk, idxChunk] : zip(valChunks, idxChunks)) {
    auto valCache = std::array<std::array<Val_t, cacheLineSize>, bankCount>{};
    auto idxCache = std::array<std::array<Idx_t, cacheLineSize>, bankCount>{};
    auto cacheFillLevels = std::array<size_t, bankCount>{};
    auto cacheTags = std::array<size_t, bankCount>{};

    for (auto &&[val, idx] : zip(valChunk, idxChunk)) {
      assert(0 <= idx && static_cast<size_t>(idx) < ranges::size(idxRng));
      auto tag = idx >> logBinSize;
      auto bank = idx & bankMask;

      auto cacheTag = cacheTags[bank];
      auto fillLevel = cacheFillLevels[bank];
      if (fillLevel == 0) {
        idxCache[bank][0] = idx;
        valCache[bank][0] = val;
        cacheFillLevels[bank] = 1;
        cacheTags[bank] = tag;
      } else if (cacheTag != tag) {
        flush(idxCache[bank], valCache[bank], fillLevel);
        idxCache[bank][0] = idx;
        valCache[bank][0] = val;
        cacheFillLevels[bank] = 1;
        cacheTags[bank] = tag;
      } else {
        idxCache[bank][fillLevel] = idx;
        valCache[bank][fillLevel] = val;
        ++cacheFillLevels[bank];

        if (fillLevel == cacheLineSize) {
          flush(idxCache[bank], valCache[bank], fillLevel);
          cacheFillLevels[bank] = 0;
        }
      }
    }

    for (size_t i = 0; i < bankCount; ++i) {
      flush(idxCache[i], valCache[i], cacheFillLevels[i]);
    }
  }
}

} // namespace direct_mapping

} // namespace pad::serial_binning

#endif //SERIAL_BINNING_H
