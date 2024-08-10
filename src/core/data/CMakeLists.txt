cmake_minimum_required(VERSION 3.21)

add_library(core_ed STATIC
  "${CMAKE_SOURCE_DIR}/src/core/data/custom_type_registry.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/data/ed.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/data/parser/lex.yy.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/data/parser/parser.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/data/parser/parser.tab.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/data/utils.cpp"
)
