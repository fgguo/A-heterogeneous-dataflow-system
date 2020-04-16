#ifndef CONNECTOR_DATAGENERATOR_HPP_
#define CONNECTOR_DATAGENERATOR_HPP_

#include "../dataflow/Vertex.hpp"

using namespace std;

class DataGenerator: public Vertex {

public:

	DataGenerator(int tag, int rank, int worldSize,bool GPU);

	~DataGenerator();

	void batchProcess();

	void streamProcess(int channel);

private:
	Window* window;

};

#endif /* CONNECTOR_DATAGENERATOR_HPP_ */
