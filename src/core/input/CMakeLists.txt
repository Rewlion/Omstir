cmake_minimum_required(VERSION 3.21)

add_library(core_input STATIC
  "${CMAKE_SOURCE_DIR}/src/core/input/drivers/drivers.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/input/drivers/windows/win_keyboard.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/input/drivers/windows/win_mouse.cpp"
  "${CMAKE_SOURCE_DIR}/src/core/input/input_router.cpp"
)
