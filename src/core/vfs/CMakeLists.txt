cmake_minimum_required(VERSION 3.21)

add_library(core_vfs STATIC
  "${CMAKE_SOURCE_DIR}/src/core/vfs/file_watcher.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/vfs/vfs.cpp"
)
