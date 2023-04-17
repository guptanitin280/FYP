cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(STREAMING)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -DFYP)

add_library(genetic_lib genetic/include/Breeder.h genetic/include/Evolver.h genetic/include/GeneticConstants.h genetic/include/GeneticSolver.h genetic/include/Genome.h genetic/include/Picker.h genetic/src/Genome.cpp genetic/heuristics/fitness_functions/TimeSaved.cpp genetic/heuristics/fitness_functions/TimeSaved.h genetic/heuristics/fitness_functions/CacheUtilisation.cpp genetic/heuristics/fitness_functions/CacheUtilisation.h)
target_sources(genetic_lib PUBLIC genetic/src/GeneticSolver.cpp )

set(SHARED_SOURCES shared/Score.cpp shared/utils.cpp  shared/Input.cpp shared/Output.cpp)

set(SA_LIB_SOURCES SimulatedAnealing/SimulatedAnealing.cpp
    SimulatedAnealing/CostEvaluator.cpp
    SimulatedAnealing/AcceptanceEvaluator.cpp
    SimulatedAnealing/SAState.cpp
    )
add_library(simulated_anealing_lib)
target_sources(simulated_anealing_lib PUBLIC ${SA_LIB_SOURCES})

add_library(heuristics_lib heuristics/RandomGreedy.cpp heuristics/RandomGreedy.h heuristics/Greedy.cpp heuristics/Greedy.h)
target_sources(heuristics_lib PUBLIC )

add_executable(SA_main SimulatedAnealing/main.cpp ${SHARED_SOURCES})
target_link_libraries(SA_main simulated_anealing_lib heuristics_lib)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
add_executable(STREAMING ${SHARED_SOURCES} main.cpp  aco/aco.cpp aco/aco.h aco/evaporatePheromone.cpp aco/replenishPheromone.cpp aco/runAnts.cpp aco/initializePheromone.cpp aco/Graph.cpp aco/Graph.h)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
target_link_libraries(STREAMING genetic_lib simulated_anealing_lib heuristics_lib)
