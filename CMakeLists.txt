cmake_minimum_required(VERSION 3.15)
project(PEA_Simulated_Annealing)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(PEA_Simulated_Annealing main.cpp AdjacencyMatrix.cpp AdjacencyMatrix.h Path.cpp Path.h ReaderFromFile.cpp ReaderFromFile.h Timer.h SimulatedAnnealing.cpp SimulatedAnnealing.h RandomGenerator.cpp RandomGenerator.h)
