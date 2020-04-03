cmake_minimum_required(VERSION 3.15)
project(01_Set_implementation)

set(CMAKE_CXX_STANDARD 14)

add_executable(Set old/Set_keys_vector.cpp)
add_executable(Set_10mln Set_10mln.cpp)