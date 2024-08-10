#pragma once

#include <core/types.h>

#include <vector>

namespace vfs
{
  void init();
  void mount_source(const string_view path, const string_view to);
  std::vector<char> read_file(const string_view path);
}
