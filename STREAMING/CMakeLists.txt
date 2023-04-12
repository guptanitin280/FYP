cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(STREAMING)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -DFYP)

add_library(genetic_lib genetic/include/Breeder.h genetic/include/Evolver.h genetic/include/GeneticConstants.h genetic/include/GeneticSolver.h genetic/include/Genome.h genetic/include/Picker.h genetic/src/Genome.cpp genetic/heuristics/fitness_functions/TimeSaved.cpp genetic/heuristics/fitness_functions/TimeSaved.h)
target_sources(genetic_lib PUBLIC genetic/src/GeneticSolver.cpp )

set(SA_LIB_SOURCES SimulatedAnealing/SimulatedAnealing.cpp
    SimulatedAnealing/CostEvaluator.cpp
    SimulatedAnealing/AcceptanceEvaluator.cpp
    SimulatedAnealing/SAState.cpp
    )
add_library(simulated_anealing_lib)
target_sources(simulated_anealing_lib PUBLIC ${SA_LIB_SOURCES})

add_library(heuristics_lib heuristics/RandomGreedy.cpp heuristics/RandomGreedy.h heuristics/Greedy.cpp heuristics/Greedy.h)
target_sources(heuristics_lib PUBLIC )

add_executable(STREAMING main.cpp shared/Score.cpp shared/Score.h shared/Input.cpp shared/Input.h)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1000000000")
target_link_libraries(STREAMING genetic_lib simulated_anealing_lib)
