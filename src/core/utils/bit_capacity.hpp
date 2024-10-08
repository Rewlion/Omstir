#pragma once

#include <core/assert.h>
#include <core/log.h>

namespace utils
{
  template<size_t N>
  class BitCapacity
  {
    static constexpr size_t batchSize = sizeof(uint64_t);
    static constexpr size_t batchesCount = (N+batchSize) / batchSize;
    using BatchType = uint64_t;

    public:
      inline void resetAll()
      {
        for (size_t i = 0; i < batchesCount; ++i)
          batches[i] = (BatchType)(0);
      }

      inline void setAll()
      {
        for (size_t i = 0; i < batchesCount; ++i)
          batches[i] = (BatchType)(~0);
      }

      inline void set(const size_t i)
      {
        ASSERT_FMT(i < N, "{} >= {} (i >= container size)", i, N);
        BatchType& batch = getBatch(i);
        const size_t j = getPosInBatch(i);
        batch |= 0x1ull << j;
      }

      inline void set(const size_t i, const bool val)
      {
        if (val)
          set(i);
        else
          reset(i);
      }

      inline void reset(const size_t i)
      {
        ASSERT_FMT(i < N, "{} >= {} (i >= container size)", i, N);
        BatchType& batch = getBatch(i);
        const size_t j = getPosInBatch(i);
        batch &= ~(0x1ull << j);
      }

      inline bool isSet(const size_t i) const
      {
        ASSERT_FMT(i < N, "{} >= {} (i >= container size)", i, N);
        const BatchType& batch = getBatch(i);
        const size_t j = getPosInBatch(i);
        size_t bit = 0x1ull & (batch >> j);

        return bit == 1;
      }

    private:
      BatchType& getBatch(const size_t i)
      {
        const size_t batchId = i/batchSize;
        return batches[batchId];
      }

      const BatchType& getBatch(const size_t i) const
      {
        return const_cast<BitCapacity&>(*this).getBatch(i);
      }

      size_t getPosInBatch(const size_t i) const
      {
        return i % batchSize;
      }

    private:
      BatchType batches[batchesCount] = {0};
  };
}
