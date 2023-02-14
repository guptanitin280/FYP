cmake_minimum_required(VERSION 3.21)
project(FYP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(FYP main.cpp algorithms/Greedy.cpp algorithms/Greedy.h algorithms/BruteForce.cpp algorithms/BruteForce.h shared/Graph.cpp shared/Graph.h shared/utils.cpp shared/utils.h shared/Score.cpp shared/Score.h ../lib/LPSolver.cpp ../lib/LPSolver.h shared/Input.h shared/Input.cpp)
