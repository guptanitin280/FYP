cmake_minimum_required(VERSION 3.21)
project(FYP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(FYP main.cpp algorithms/BruteForce.cpp algorithms/BruteForce.h algorithms/Score.cpp algorithms/Score.h ../lib/LPSolver.cpp ../lib/LPSolver.h algorithms/Input.h algorithms/Input.cpp)
