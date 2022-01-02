cmake_minimum_required(VERSION 3.7)
project(raytracer)

find_package(SDL2 REQUIRED)
set(CMAKE_BUILD_TYPE Debug)
find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(raytracer ${SDL2_LIBRARIES})

