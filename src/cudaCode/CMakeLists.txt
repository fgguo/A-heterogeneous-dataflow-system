# required cmake version
cmake_minimum_required(VERSION 2.8)

project(GPU)

# packages
find_package(CUDA)

# nvcc flags
#set(CUDA_NVCC_FLAGS -O3;-G;-g)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp *.cuh)
file(GLOB CURRENT_SOURCES  *.cpp *.cu)

source_group("include" FILES ${CURRENT_HEADERS})
source_group("src" FILES ${CURRENT_SOURCES})

cuda_add_library(GPU STATIC ${CURRENT_HEADERS} ${CURRENT_SOURCES})