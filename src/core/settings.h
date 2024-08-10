#pragma once

#include <core/data/ed.h>

namespace settings
{
  void load_app_settings(const string_view path);
  auto get_app_settings() -> ed::Scope&;
}
