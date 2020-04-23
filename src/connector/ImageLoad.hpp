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
	int numImgs;//ÿ�ζ�ȡ��ͼ������
};

#endif /* CONNECTOR_IMAGELOAD_HPP_ */
