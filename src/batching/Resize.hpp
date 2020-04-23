/*
 Resize.hpp
 Created on: 4 19, 2020
 Author: Fu GUo
 */
#ifndef BATCHING_RESIZE_HPP_
#define BATCHING_RESIZE_HPP_

#include "../dataflow/Vertex.hpp"
#include "../cudaCode/multi.cuh"

using namespace std;

class Resize: public Vertex {

public:

	Resize(int tag, int rank, int worldSize,bool GPU,int width,int height);

	~Resize();

	void batchProcess();
	void streamProcess(int channel);

private:
	int width,height;
	Window* window;

	
};

#endif /* BATCHING_RESIZE_HPP_ */
