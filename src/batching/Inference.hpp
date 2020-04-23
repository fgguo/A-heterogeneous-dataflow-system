/*
 Inference.hpp
 Created on: 4 19, 2020
 Author: Fu GUo
 */
#ifndef BATCHING_INFERENCE_HPP_
#define BATCHING_INFERENCE_HPP_

#include "../dataflow/Vertex.hpp"
#include "../cudaCode/MatrixMul.cuh"

using namespace std;

class Inference: public Vertex {

public:

	Inference(int tag, int rank, int worldSize,bool GPU);

	~Inference();

	void batchProcess();
	void streamProcess(int channel);

private:
	Window *window;
	
};

#endif /* BATCHING_INFERENCE_HPP_ */
