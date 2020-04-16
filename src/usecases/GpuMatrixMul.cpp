/*
 * GpuMR.hpp
 *
 *  Created on: 4 13, 2020
 *      Author: Fu GUo
 */
#include "GpuMatrixMul.hpp"
#include "../connector/DataGenerator.hpp"
#include "../dataflow/Vertex.hpp"
#include "../batching/MatrixMul.hpp"

using namespace std;

GpuMatrixMul::GpuMatrixMul() :
		Dataflow() {

	generator = new DataGenerator(0, rank, worldSize,false);
	matrixmul = new MatrixMul(1, rank, worldSize,true);
	// Simple chain
	addLink(generator,matrixmul);
	generator ->initialize();
	matrixmul ->initialize();
	}

GpuMatrixMul::~GpuMatrixMul() {
	delete generator ;
	delete matrixmul ;
}
