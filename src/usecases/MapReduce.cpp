

#include "MapReduce.hpp"

#include "../batching/Map.hpp"
#include "../batching/Reduce.hpp"
#include "../connector/BinConnector.hpp"
#include "../dataflow/Vertex.hpp"
#include "../function/SquareFunction.hpp"
#include "../function/SumFunction.hpp"

using namespace std;

MapReduce::MapReduce() :
		Dataflow() {

	connector = new BinConnector("../data/INT_64MB.bin", 0, rank, worldSize,false);
	mapper = new Map(new SquareFunction(), 1, rank, worldSize,false);
	reducer = new Reduce(new SumFunction(), 2, rank, worldSize,false);

	// Simple chain
	addLink(connector, mapper);
	addLink(mapper, reducer);

	connector->initialize();
	mapper->initialize();
	reducer->initialize();
}

MapReduce::~MapReduce() {
	delete connector;
	delete mapper;
	delete reducer;
}
