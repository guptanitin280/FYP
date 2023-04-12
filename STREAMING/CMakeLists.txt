cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(STREAMING)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -DFYP)

add_executable(STREAMING main.cpp shared/Score.cpp shared/Score.h shared/Input.cpp shared/Input.h)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1000000000")
