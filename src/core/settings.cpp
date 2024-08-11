#include "settings.h"

#include <core/assert.h>
#include <core/data/utils.h>
#include <core/log.h>

namespace settings
{
  static ed::Scope SETTINGS_DATA;

  void load_app_settings(const string_view file)
  {
    std::optional<ed::Scope> settings = ed::load_from_file(file);

    ASSERT_FMT_RETURN(settings.has_value(), ,
      "failed to load application settings from {}", file);

    SETTINGS_DATA = std::move(settings.value());
  }

  ed::Scope& get_app_settings()
  {
    return SETTINGS_DATA;
  }
}