#include "Reduce.hpp"
#include "../cudaCode/sum.cuh"
#include <iostream>
#include <vector>

#include "../communication/Message.hpp"
#include "../dataflow/Vertex.hpp"
#include "../function/Function.hpp"
#include "../partitioning/Partition.hpp"
#include "../serialization/Serialization.hpp"

using namespace std;

Reduce::Reduce(Function* func, int tag, int rank, int worldSize,bool GPU) :
		Vertex(tag, rank, worldSize,GPU) {
	this->func = func;
}

Reduce::~Reduce() {
}

void Reduce::batchProcess() {

	cout << "REDUCE->BATCHPROCESS [" << tag << "] @ " << rank << endl;

	Serialization ser;
	Partition<int> partitions[previous.size() * worldSize];

	long long totalSumOfSquares = 0;
	if(GPU){
	for (int i = 0; i < previous.size() * worldSize; i++) {	
		totalSumOfSquares = sum(rMessages[i]->buffer,rMessages[i]->size);
		}
	}
	else{
	for (int i = 0; i < previous.size() * worldSize; i++) {	
		ser.deserialize(rMessages[i], &partitions[i]);
		totalSumOfSquares += func->combine(&partitions[i]);
		}
	}
	// SHOW FINAL RESULT
	cout << "TOTAL_SUM_OF_SQUARES: " << totalSumOfSquares << endl;
}
