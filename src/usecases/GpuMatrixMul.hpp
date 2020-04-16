/*
 * GpuMatrixMul.hpp
 *
 *  Created on: 4 13, 2020
 *      Author: Fu GUo
 */

#ifndef USECASES_GPUMATRIXMUL_HPP_
#define USECASES_GPUMATRIXMUL_HPP_

#include "../dataflow/Dataflow.hpp"

using namespace std;

class GpuMatrixMul: public Dataflow {

public:

	Vertex *generator, *matrixmul;

	GpuMatrixMul();

	~GpuMatrixMul();

};

#endif /* USECASES_GPUMATRIXMUL_HPP_ */
