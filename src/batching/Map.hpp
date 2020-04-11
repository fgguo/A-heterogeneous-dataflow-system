
/*
 * Map.hpp
 *
 *  Created on: Dec 20, 2017
 *      Author: martin.theobald, amal.tawakuli
 */

#ifndef BATCHING_MAP_HPP_
#define BATCHING_MAP_HPP_

#include "../dataflow/Vertex.hpp"
#include "../cudaCode/multi.cuh"

using namespace std;

class Map: public Vertex {

public:

	Map(Function* func, int tag, int rank, int worldSize,bool GPU);

	~Map();

	void batchProcess();
	void streamProcess(int channel);

private:

	Function* func; // Actual function to be processed by the transformation

};

#endif /* BATCHING_MAP_HPP_ */
