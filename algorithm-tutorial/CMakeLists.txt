cmake_minimum_required(VERSION 3.23)
project(algorithm_tutorial)

set(CMAKE_CXX_STANDARD 14)

add_executable(algorithm_tutorial
        main.cpp src/headers/comm.h
        src/headers/refer.h
        src/tutorials/graphs/AdjacencyListGraph.cpp
        src/tutorials/dijksta/Test1.cpp
        src/tutorials/dijksta/Test2.cpp
        src/tutorials/dijksta/Test3.cpp
        src/tutorials/dijksta/Test4.cpp
        src/tutorials/DirectionGraph/demo1.cpp)
