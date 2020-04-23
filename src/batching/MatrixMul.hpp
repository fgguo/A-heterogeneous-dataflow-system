/*
 GpuMatrixMul.hpp
 Created on: 4 13, 2020
 Author: Fu GUo
 */
#ifndef BATCHING_MATRIXMUL_HPP_
#define BATCHING_MATRIXMUL_HPP_

#include "../dataflow/Vertex.hpp"
#include "../cudaCode/multi.cuh"

using namespace std;

class MatrixMul: public Vertex {

public:

	MatrixMul(int tag, int rank, int worldSize,bool GPU);

	~MatrixMul();

	void batchProcess();
	void streamProcess(int channel);

private:

	
};

#endif /* BATCHING_MATRIXMUL_HPP_ */
