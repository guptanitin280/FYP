cmake_minimum_required(VERSION 3.21)
project(FYP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES algorithms/Greedy.cpp
            algorithms/BruteForce.cpp 
            shared/Graph.cpp 
            shared/utils.cpp 
            shared/Score.cpp 
            shared/Input.cpp
            algorithms/SimulatedAnealing/SimulatedAnealing.cpp
            algorithms/SimulatedAnealing/CostEvaluator.cpp
            )

add_library(optimization_lib)
target_sources(optimization_lib PUBLIC ${SOURCES})
add_executable(FYP main.cpp)
target_link_libraries(FYP optimization_lib)
