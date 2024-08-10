cmake_minimum_required(VERSION 3.21)

add_subdirectory("${CMAKE_SOURCE_DIR}/src/core/data")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/core/utils")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/core/vfs")

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/xxHash/cmake_unofficial" "${CMAKE_SOURCE_DIR}/deps/xxHash/build" EXCLUDE_FROM_ALL)

add_library(core STATIC
  "${CMAKE_SOURCE_DIR}/src/core/assert.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/log.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/settings.cpp"
)

target_link_libraries(
  core
  core_ed
  core_utils
  core_vfs

  xxHash::xxhash
)