

/*
 * GpuMR.hpp
 *
 *  Created on: 4 10, 2020
 *      Author: Fu GUo
 */

#ifndef USECASES_GPUMAPREDUCE_HPP_
#define USECASES_GPUMAPREDUCE_HPP_

#include "../dataflow/Dataflow.hpp"

using namespace std;

class GpuMR: public Dataflow {

public:

	Vertex *connector, *mapper, *reducer;

	GpuMR();

	~GpuMR();

};

#endif /* USECASES_MAPREDUCE_HPP_ */
