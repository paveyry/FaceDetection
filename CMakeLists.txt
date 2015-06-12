cmake_minimum_required(VERSION 2.8)

project(ObjectDetection)

set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++14 -pedantic -O3 -fPIC")

file(
  GLOB_RECURSE
  sources_files
  src/*
  )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
add_executable(
  objdetect
  ${sources_files}
  )

target_link_libraries(objdetect tbb rt)
