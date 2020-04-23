#ifndef CONNECTOR_IMAGELOAD_HPP_
#define CONNECTOR_IMAGELOAD_HPP_

#include "../dataflow/Vertex.hpp"
using namespace std;

class ImageLoad: public Vertex {

public:

	ImageLoad(string fileName,int numImgs,int tag, int rank, int worldSize,bool GPU);

	~ImageLoad();

	void batchProcess();

	void streamProcess(int channel);

private:
	Window* window;
	string fileName;
	int numImgs;//每次读取的图像数量
};

#endif /* CONNECTOR_IMAGELOAD_HPP_ */
