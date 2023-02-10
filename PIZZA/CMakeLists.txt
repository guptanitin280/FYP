cmake_minimum_required(VERSION 3.21)
project(FYP)

set(CMAKE_CXX_STANDARD 20)

add_executable(FYP main.cpp algorithms/Brute_force.cpp algorithms/Brute_force.h algorithms/Score.cpp algorithms/Score.h ../lib/LPSolver.cpp ../lib/LPSolver.h)
