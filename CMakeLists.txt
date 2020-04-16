#cmake_minimum_required(VERSION 3.15)
project(AIR)
add_subdirectory(src/cudaCode)
set(CMAKE_CXX_STANDARD 14)

set(COMPILER_PATH "/usr/local/bin/")

set(CMAKE_CXX_COMPILER "${COMPILER_PATH}/mpic++")
include_directories(/home/fug/software/AIR-master/local)
include_directories(include)
include_directories(include/json)
include_directories(src/batching)
include_directories(src/communication)
include_directories(src/configuration)
include_directories(src/connector)
include_directories(src/dataflow)
include_directories(src/function)
include_directories(src/input)
include_directories(src/output)
include_directories(src/partitioning)
include_directories(src/serialization)
include_directories(src/usecases)


add_executable(AIR
        src/batching/Map.cpp
        src/batching/Map.hpp
        src/batching/Reduce.cpp
        src/batching/Reduce.hpp
	src/batching/MatrixMul.cpp
        src/batching/MatrixMul.hpp
        src/communication/Message.cpp
        src/communication/Message.hpp
        src/communication/Window.cpp
        src/communication/Window.hpp
        src/configuration/HashConfig.hpp
        src/connector/BinConnector.cpp
        src/connector/BinConnector.hpp
   	src/connector/DataGenerator.cpp
        src/connector/DataGenerator.hpp
        src/dataflow/Dataflow.cpp
        src/dataflow/Dataflow.hpp
        src/dataflow/Vertex.cpp
        src/dataflow/Vertex.hpp
        src/function/Function.cpp
        src/function/Function.hpp
        src/function/SquareFunction.cpp
        src/function/SquareFunction.hpp
        src/function/SumFunction.cpp
        src/function/SumFunction.hpp
        src/input/FileInput.cpp
        src/input/FileInput.hpp
        src/input/Input.cpp
        src/input/Input.hpp
        src/main/main.cpp
        src/output/FileOutput.cpp
        src/output/FileOutput.hpp
        src/output/Output.cpp
        src/output/Output.hpp
        src/partitioning/Hash.cpp
        src/partitioning/Hash.hpp
        src/partitioning/PairPartition.hpp
        src/partitioning/Partition.hpp
        src/serialization/Serialization.cpp
        src/serialization/Serialization.hpp
        src/usecases/MapReduce.cpp
        src/usecases/MapReduce.hpp
 	src/usecases/GpuMatrixMul.cpp
        src/usecases/GpuMatrixMul.hpp
        src/usecases/GpuMR.cpp
        src/usecases/GpuMR.hpp)

target_link_libraries (AIR GPU)
