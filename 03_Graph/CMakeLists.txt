cmake_minimum_required(VERSION 3.15)
project(03_Graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(L_Graph adjacency_list_graph.cpp)
add_executable(M_Graph adjacency_matrix_graph.cpp)