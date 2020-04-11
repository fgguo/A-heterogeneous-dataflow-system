
/*
 * Reduce.hpp
 *
 *  Created on: Dec 22, 2017
 *      Author: martin.theobald, amal.tawakuli
 */

#ifndef BATCHING_REDUCE_HPP_
#define BATCHING_REDUCE_HPP_

#include "../dataflow/Vertex.hpp"

using namespace std;

class Reduce: public Vertex {

public:

	Reduce(Function* func, int tag, int rank, int worldSize,bool GPU);

	~Reduce();

	void batchProcess();

private:

	Function* func; // Actual function to be processed by the transformation

};

#endif /* BATCHING_REDUCE_HPP_ */
