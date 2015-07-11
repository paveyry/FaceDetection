cmake_minimum_required(VERSION 2.6)
project(face-recog)
set(EXECUTABLE_NAME "face-recog")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -pedantic -fPIC")

# Define sources and executable
file(GLOB_RECURSE sources_files src/*)
add_executable(${EXECUTABLE_NAME} ${sources_files})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
