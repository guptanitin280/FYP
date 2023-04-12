cmake_minimum_required(VERSION 3.21)
project(FYP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)


add_library(genetic_lib genetic_algorithm/include/GeneticConstants.h genetic_algorithm/heuristics/fitness_functions/SumOfDegrees.cpp genetic_algorithm/heuristics/fitness_functions/SumOfDegrees.h genetic_algorithm/heuristics/fitness_functions/CountAndSum.cpp genetic_algorithm/heuristics/fitness_functions/CountAndSum.h)
target_sources(genetic_lib PUBLIC genetic_algorithm/heuristics/fitness_functions/NumberOfOnes.cpp genetic_algorithm/heuristics/fitness_functions/NumberOfOnes.h genetic_algorithm/include/Breeder.h genetic_algorithm/include/Evolver.h genetic_algorithm/include/GeneticSolver.h genetic_algorithm/include/Genome.h genetic_algorithm/include/Picker.h genetic_algorithm/src/GeneticSolver.cpp genetic_algorithm/src/Genome.cpp
        )

    add_library(heuristics_lib heuristics/RandomGreedy.cpp heuristics/RandomGreedy.h heuristics/RandomInit.cpp heuristics/RandomInit.h)
target_sources(heuristics_lib PUBLIC heuristics/Greedy.cpp heuristics/Greedy.h)

set(SA_LIB_SOURCES algorithms/SimulatedAnealing/SimulatedAnealing.cpp
    algorithms/SimulatedAnealing/CostEvaluator.cpp
    algorithms/SimulatedAnealing/AcceptanceEvaluator.cpp)

file(GLOB ACO_LIB_SOURCES "algorithms/aco/*.cpp")
add_library(optimization_lib )
target_sources(optimization_lib PUBLIC algorithms/aco/aco.h algorithms/aco/aco.cpp algorithms/Greedy.cpp algorithms/BruteForce.cpp algorithms/BruteForce.h shared/Graph.cpp shared/Graph.h shared/utils.cpp shared/utils.h shared/Score.cpp shared/Score.h  shared/Input.h shared/Input.cpp)
add_executable(FYP main.cpp ${SA_LIB_SOURCES} ${ACO_LIB_SOURCES})
target_link_libraries(FYP optimization_lib genetic_lib heuristics_lib)

