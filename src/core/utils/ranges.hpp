#pragma once

#include <core/types.h>

#include <ranges>

namespace ranges
{
  inline
  auto enumerate_substrings(const string_view str, string_view delim)
  {
    return str | std::views::split(delim)
               | std::views::transform([](const auto& rng)
               {
                return string_view{rng.begin(), rng.end()};
               })
               | std::views::filter([](const auto& view)
               {
                 return view != "";
               });
  }
}