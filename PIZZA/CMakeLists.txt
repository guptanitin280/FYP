cmake_minimum_required(VERSION 3.21)
project(FYP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_library(genetic_lib)
target_sources(genetic_lib PUBLIC genetic_algorithm/heuristics/fitness_functions/NumberOfOnes.cpp genetic_algorithm/heuristics/fitness_functions/NumberOfOnes.h genetic_algorithm/include/Breeder.h genetic_algorithm/include/Evolver.h genetic_algorithm/include/GeneticSolver.h genetic_algorithm/include/Genome.h genetic_algorithm/include/Picker.h genetic_algorithm/src/GeneticSolver.cpp genetic_algorithm/src/Genome.cpp
        )

add_library(heuristics_lib)
target_sources(heuristics_lib PUBLIC heuristics/Greedy.cpp heuristics/Greedy.h)

add_library(optimization_lib )
target_sources(optimization_lib PUBLIC algorithms/aco/aco.h algorithms/aco/aco.cpp algorithms/Greedy.cpp algorithms/Greedy.h algorithms/BruteForce.cpp algorithms/BruteForce.h shared/Graph.cpp shared/Graph.h shared/utils.cpp shared/utils.h shared/Score.cpp shared/Score.h  shared/Input.h shared/Input.cpp)
add_executable(FYP main.cpp )
target_link_libraries(FYP optimization_lib genetic_lib heuristics_lib)
