cmake_minimum_required(VERSION 3.21)
project(FYP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_library(optimization_lib)
target_sources(optimization_lib PUBLIC algorithms/Greedy.cpp algorithms/Greedy.h algorithms/BruteForce.cpp algorithms/BruteForce.h shared/Graph.cpp shared/Graph.h shared/utils.cpp shared/utils.h shared/Score.cpp shared/Score.h  shared/Input.h shared/Input.cpp)
add_executable(FYP main.cpp)
target_link_libraries(FYP optimization_lib)
