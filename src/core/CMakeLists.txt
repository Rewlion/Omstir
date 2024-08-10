cmake_minimum_required(VERSION 3.21)

set(CORE_SRC
  "${CMAKE_SOURCE_DIR}/src/core/log.cpp"
)

add_library(core ${CORE_SRC})
