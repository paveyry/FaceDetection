cmake_minimum_required(VERSION 2.8)

project(FaceRecog)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CPP_FLAGS "`pkg-config --cflags sdl`")
set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++14 -pedantic -fPIC")

find_package(SDL)

file(GLOB_RECURSE sources_files src/*)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_executable(face-recog ${sources_files})

target_link_libraries(face-recog tbb rt ${SDL_LIBRARY})
