#pragma once


#include <spdlog/spdlog.h>
#undef NEAR
#undef FAR
#undef near
#undef far

namespace log
{
  void init();
  spdlog::logger* get_logger();
}


#define logdbg(...)  log::get_logger()->debug(__VA_ARGS__)
#define loginfo(...) log::get_logger()->info(__VA_ARGS__)
#define logwarn(...) log::get_logger()->warn(__VA_ARGS__)
#define logerr(...)  log::get_logger()->error(__VA_ARGS__)
