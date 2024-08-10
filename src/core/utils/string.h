#pragma once

#include <core/types.h>

#include <vector>
#include <functional>

namespace Utils
{
  auto remove_spaces(const string& str) -> string;
  auto split(const string& str, char delim) -> std::vector<string>;
  auto split_view(const string_view str, char delim) -> std::vector<string_view>;
  void for_each_view_substr(const string_view str, 
                            const string_view delim, 
                            std::function<bool(const string_view)>);
  bool find_view_substr(const string_view str, 
                        const string_view delim, 
                        std::function<bool(const string_view)>);
}
