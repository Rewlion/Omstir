#include "time.h"

#include <windows.h>

namespace clocks
{
  static uint64_t perf_counter_frequency = 0;
  static uint64_t start_hires_clock = 0;
  static uint64_t last_hires_clock = 0;

  static uint64_t hires_dt = 0;
  static uint64_t ms_dt = 0;
  static uint64_t us_dt = 0;

  static uint64_t get_hires_clock()
  {
    LARGE_INTEGER largeInt;
    if (QueryPerformanceCounter(&largeInt))
      return largeInt.QuadPart;
    else
      return 0;
  }

  bool init()
  {
    LARGE_INTEGER largeInt;
    const BOOL queriedFreq = QueryPerformanceFrequency(&largeInt);

    if (!queriedFreq)
      return false;

    perf_counter_frequency = largeInt.QuadPart;
    start_hires_clock = get_hires_clock();
    last_hires_clock = start_hires_clock;

    return true;
  }

  void tick()
  {
    const uint64_t current_time = get_hires_clock();
    hires_dt = current_time - last_hires_clock;
    last_hires_clock = current_time;

    ms_dt = (hires_dt * 1000) / perf_counter_frequency;
    us_dt = (hires_dt * 1000000) / perf_counter_frequency;
  }

  uint64_t get_time_since_start()
  {
    return last_hires_clock - start_hires_clock;
  }

  uint64_t get_time_ms_since_start()
  {
    return (last_hires_clock * 1000) / perf_counter_frequency;
  }

  float get_sec_since_start()
  {
    return convert_to_sec(get_time_since_start());
  }

  float get_dt()
  {
    return static_cast<float>(ms_dt) / 1000.0f;
  }

  float convert_to_sec(uint64_t rawTime)
  {
    return (float)rawTime / (float)perf_counter_frequency;
  }

  uint64_t convert_sec_to_clocks(uint64_t sec)
  {
    return sec * perf_counter_frequency;
  }
}