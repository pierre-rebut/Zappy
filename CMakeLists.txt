cmake_minimum_required(VERSION 3.0)
project(zappy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE INCLUDES *.h)

add_subdirectory(graph_dir)
