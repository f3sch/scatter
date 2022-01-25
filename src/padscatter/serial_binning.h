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
#include <span>

namespace pad::serial_binning {


namespace detail
{
inline constexpr size_t log2(size_t x)
{
  return __builtin_ctz(x);
}
}

template <size_t chunkSize = 1024, size_t binSize = 64, typename OutIt_t, typename InRng_t, typename IdxRng_t>
void scatter(OutIt_t outIt, const InRng_t &inRng, const IdxRng_t &idxRng) {
  using namespace ranges;
  using namespace ranges::view;
  using Idx_t = std::ranges::range_value_t<IdxRng_t>;
  using Val_t = std::ranges::range_value_t<InRng_t>;

  struct KeyValPair {
    Idx_t idx;
    Val_t val;
  };

  auto flush = [&](auto &&bin){
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
  KeyValPair *bin0Begin = bin0.data();
  KeyValPair *bin1Begin = bin1.data();
  KeyValPair *bin2Begin = bin2.data();
  KeyValPair *bin3Begin = bin3.data();
  KeyValPair *bin4Begin = bin4.data();
  KeyValPair *bin5Begin = bin5.data();
  KeyValPair *bin6Begin = bin6.data();
  KeyValPair *bin7Begin = bin7.data();
  KeyValPair *bin7End = &*bin7.end();
  KeyValPair *bin0It = bin0.data();
  KeyValPair *bin1It = bin1.data();
  KeyValPair *bin2It = bin2.data();
  KeyValPair *bin3It = bin3.data();
  KeyValPair *bin4It = bin4.data();
  KeyValPair *bin5It = bin5.data();
  KeyValPair *bin6It = bin6.data();
  KeyValPair *bin7It = bin7.data();

  std::uniform_int_distribution dist{0, 7};
  std::mt19937 random_engine {std::random_device{}()};

  for (auto &&[valChunk, idxChunk] : zip(valChunks, idxChunks)) {
    for (auto &&[val, idx] : zip(valChunk, idxChunk)) {
      assert(0 <= idx && static_cast<size_t>(idx) < ranges::size(idxRng));
      auto tag = idx >> logBinSize;
      if (tag == bin0Tag) {
        *bin0It = { idx, val };
        ++bin0It;

        if (bin0It == bin1Begin) {
          flush(bin0);
          bin0It = bin0Begin;
          bin0Tag = empty_tag;
        }
      } else if (tag == bin1Tag) {
        *bin1It = { idx, val };
        ++bin1It;

        if (bin1It == bin2Begin) {
          flush(bin1);
          bin1It = bin1Begin;
          bin1Tag = empty_tag;
        }
      } else if (tag == bin2Tag) {
        *bin2It = { idx, val };
        ++bin2It;

        if (bin2It == bin3Begin) {
          flush(bin2);
          bin2It = bin2Begin;
          bin2Tag = empty_tag;
        }
      } else if (tag == bin3Tag) {
        *bin3It = { idx, val };
        ++bin3It;

        if (bin3It == bin4Begin) {
          flush(bin3);
          bin3It = bin3Begin;
          bin3Tag = empty_tag;
        }
      } else if (tag == bin4Tag) {
        *bin4It = { idx, val };
        ++bin4It;

        if (bin4It == bin5Begin) {
          flush(bin4);
          bin4It = bin4Begin;
          bin4Tag = empty_tag;
        }
      } else if (tag == bin5Tag) {
        *bin5It = { idx, val };
        ++bin5It;

        if (bin5It == bin6Begin) {
          flush(bin5);
          bin5It = bin5Begin;
          bin5Tag = empty_tag;
        }
      } else if (tag == bin6Tag) {
        *bin6It = { idx, val };
        ++bin6It;

        if (bin6It == bin7Begin) {
          flush(bin6);
          bin6It = bin6Begin;
          bin6Tag = empty_tag;
        }
      } else if (tag == bin7Tag) {
        *bin7It = { idx, val };
        ++bin7It;

        if (bin7It == bin7End) {
          flush(bin7);
          bin7It = bin7Begin;
          bin7Tag = empty_tag;
        }
      } else {
        if (bin0Tag == empty_tag) {
          bin0Tag = tag;
          *bin0It = { idx, val };
          ++bin0It;
        } else if (bin1Tag == empty_tag) {
          bin1Tag = tag;
          *bin1It = { idx, val };
          ++bin1It;
        } else if (bin2Tag == empty_tag) {
          bin2Tag = tag;
          *bin2It = { idx, val };
          ++bin2It;
        } else if (bin3Tag == empty_tag) {
          bin3Tag = tag;
          *bin3It = { idx, val };
          ++bin3It;
        } else if (bin4Tag == empty_tag) {
          bin4Tag = tag;
          *bin4It = { idx, val };
          ++bin4It;
        } else if (bin5Tag == empty_tag) {
          bin5Tag = tag;
          *bin5It = { idx, val };
          ++bin5It;
        } else if (bin6Tag == empty_tag) {
          bin6Tag = tag;
          *bin6It = { idx, val };
          ++bin6It;
        } else if (bin7Tag == empty_tag) {
          bin7Tag = tag;
          *bin7It = { idx, val };
          ++bin7It;
        } else {
          auto randomBin = dist(random_engine);
          if (randomBin == 0) {
            flush(std::ranges::subrange(bin0Begin, bin0It));
            bin0It = bin0Begin;
            bin0Tag = tag;
            *bin0It = { idx, val };
            ++bin0It;
          } else if (randomBin == 1) {
            flush(std::ranges::subrange(bin1Begin, bin1It));
            bin1It = bin1Begin;
            bin1Tag = tag;
            *bin1It = { idx, val };
            ++bin1It;
          } else if (randomBin == 2) {
            flush(std::ranges::subrange(bin2Begin, bin2It));
            bin2It = bin2Begin;
            bin2Tag = tag;
            *bin2It = { idx, val };
            ++bin2It;
          } else if (randomBin == 3) {
            flush(std::ranges::subrange(bin3Begin, bin3It));
            bin3It = bin3Begin;
            bin3Tag = tag;
            *bin3It = { idx, val };
            ++bin3It;
          } else if (randomBin == 4) {
            flush(std::ranges::subrange(bin4Begin, bin4It));
            bin4It = bin4Begin;
            bin4Tag = tag;
            *bin4It = { idx, val };
            ++bin4It;
          } else if (randomBin == 5) {
            flush(std::ranges::subrange(bin5Begin, bin5It));
            bin5It = bin5Begin;
            bin5Tag = tag;
            *bin5It = { idx, val };
            ++bin5It;
          } else if (randomBin == 6) {
            flush(std::ranges::subrange(bin6Begin, bin6It));
            bin6It = bin6Begin;
            bin6Tag = tag;
            *bin6It = { idx, val };
            ++bin6It;
          } else if (randomBin == 7) {
            flush(std::ranges::subrange(bin7Begin, bin7It));
            bin7It = bin7Begin;
            bin7Tag = tag;
            *bin7It = { idx, val };
            ++bin7It;
          }
        }
      }
    }


    flush(std::ranges::subrange(bin0Begin, bin0It));
    flush(std::ranges::subrange(bin1Begin, bin1It));
    flush(std::ranges::subrange(bin2Begin, bin2It));
    flush(std::ranges::subrange(bin3Begin, bin3It));
    flush(std::ranges::subrange(bin4Begin, bin4It));
    flush(std::ranges::subrange(bin5Begin, bin5It));
    flush(std::ranges::subrange(bin6Begin, bin6It));
    flush(std::ranges::subrange(bin7Begin, bin7It));
    bin0It = bin0Begin;
    bin1It = bin1Begin;
    bin2It = bin2Begin;
    bin3It = bin3Begin;
    bin4It = bin4Begin;
    bin5It = bin5Begin;
    bin6It = bin6Begin;
    bin7It = bin7Begin;

  }
}
} // namespace pad::serial

#endif //SERIAL_BINNING_H
