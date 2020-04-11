

#ifndef CONNECTOR_BINCONNECTOR_HPP_
#define CONNECTOR_BINCONNECTOR_HPP_

#include "../dataflow/Vertex.hpp"
#include "../input/Input.hpp"

using namespace std;

class BinConnector: public Vertex {

public:

	BinConnector(string fileName, int tag, int rank, int worldSize,bool GPU);

	~BinConnector();

	void batchProcess();

	void streamProcess(int channel);

private:

	Input* input;

	Window* window;

};

#endif /* CONNECTOR_BINCONNECTOR_HPP_ */
