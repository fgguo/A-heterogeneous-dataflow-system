# required cmake version
cmake_minimum_required(VERSION 2.8)

project(host)

add_executable(host host.cpp)

add_subdirectory(cudaCode)
target_link_libraries (host GPU)