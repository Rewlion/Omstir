cmake_minimum_required(VERSION 3.21)

add_library(core_utils STATIC
  "${CMAKE_SOURCE_DIR}/src/core/utils/fs.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/utils/string.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/utils/string_map.cpp"
)
