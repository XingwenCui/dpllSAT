cmake_minimum_required(VERSION 3.24)
project(dpllSAT)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")
add_executable(dpllSAT main.cpp DimacsParser.h common.h DPLL.h DPLL.cpp)
