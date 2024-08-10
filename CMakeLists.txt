cmake_minimum_required(VERSION 3.21)

project(Not_this_again VERSION 0.2
        DESCRIPTION "<=*_*=>"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
  "${CMAKE_SOURCE_DIR}/src/"
  "${CMAKE_SOURCE_DIR}/deps/glm/include"
  "${CMAKE_SOURCE_DIR}/deps/spdlog/include"
  "${CMAKE_SOURCE_DIR}/deps/xxHash/include"
)

add_subdirectory("${CMAKE_SOURCE_DIR}/src")