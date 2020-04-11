# required cmake version
cmake_minimum_required(VERSION 2.8)

project(VecAdd)

add_executable(VecAdd host.cpp)

add_subdirectory(cudaCode)
target_link_libraries (VecAdd GPU)