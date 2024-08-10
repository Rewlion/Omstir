cmake_minimum_required(VERSION 3.21)


file(GLOB OMSTIR_SRC
  "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(omstir ${OMSTIR_SRC})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  SET(omstir_output_name "omstir-debug")
else()
  SET(omstir_output_name "omstir-release")
endif ()

set_target_properties(omstir PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/app/omstir"
                      OUTPUT_NAME "${aster_output_name}")