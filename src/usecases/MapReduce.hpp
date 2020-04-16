
#ifndef USECASES_MAPREDUCE_HPP_
#define USECASES_MAPREDUCE_HPP_

#include "../dataflow/Dataflow.hpp"

using namespace std;

class MapReduce: public Dataflow {

public:

	Vertex *connector, *mapper, *reducer;

	MapReduce();

	~MapReduce();

};

#endif /* USECASES_MAPREDUCE_HPP_ */
