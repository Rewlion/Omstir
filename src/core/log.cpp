#include "log.h"

#include <core/types.h>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <ctime>
#include <iomanip>
#include <memory>
#include <sstream>

namespace log
{
  spdlog::logger LOGGER = spdlog::logger("multi_sink", {});

  static std::string GetTimeString()
  {
    auto t = std::time(nullptr);
    tm tm;
    errno_t e = ::localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");

    return oss.str();
  }

  void init()
  {
    const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%^%l%$] %v");

    const string timeStr = GetTimeString();
    const string logFile = fmt::format("logs/{}.log.txt",timeStr);

    const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile.c_str(), true);
    file_sink->set_level(spdlog::level::trace);

    LOGGER = spdlog::logger("", {console_sink, file_sink});
    LOGGER.set_pattern("%H:%M:%S [%^%L%$] %v");
  }

  spdlog::logger* get_logger()
  {
    return &LOGGER;
  }
}