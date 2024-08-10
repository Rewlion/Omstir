cmake_minimum_required(VERSION 3.21)

add_library(core
  "${CMAKE_SOURCE_DIR}/src/core/assert.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/log.cpp"
)

target_link_libraries(
  core
)