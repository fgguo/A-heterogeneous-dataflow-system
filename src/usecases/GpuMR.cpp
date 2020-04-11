

#include "GpuMR.hpp"

#include "../batching/Map.hpp"
#include "../batching/Reduce.hpp"
#include "../connector/BinConnector.hpp"
#include "../dataflow/Vertex.hpp"
#include "../function/SquareFunction.hpp"
#include "../function/SumFunction.hpp"

using namespace std;

GpuMR::GpuMR() :
		Dataflow() {

	connector = new BinConnector("../data/INT_64MB.bin", 0, rank, worldSize,false);
	mapper = new Map(new SquareFunction(), 1, rank, worldSize,true);
	reducer = new Reduce(new SumFunction(), 2, rank, worldSize,true);

	// Simple chain
	addLink(connector, mapper);
	addLink(mapper, reducer);

	connector->initialize();
	mapper->initialize();
	reducer->initialize();
}

GpuMR::~GpuMR() {
	delete connector;
	delete mapper;
	delete reducer;
}
