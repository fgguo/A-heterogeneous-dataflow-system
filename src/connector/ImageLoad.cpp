/*
ImageLoad.cpp
2020 4 19 by Fu Guo
*/
#include "ImageLoad.hpp"
#include <unistd.h>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <opencv2/opencv.hpp>
#include<math.h>
#include <string> 
#include<fstream> 
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../communication/Message.hpp"
#include "../communication/Window.hpp"
using namespace cv;
using namespace std;

ImageLoad::ImageLoad(string fileName,int numImgs,int tag, int rank, int worldSize,bool GPU) :
		Vertex(tag, rank, worldSize,GPU) {
	this->window = new Window(WINDOW_SIZE);
	this->fileName = fileName;
	this->numImgs = numImgs;
	this->GPU=GPU;
	cout << "ImageLoad[" << tag << "] CREATED @ "
			<< rank << endl;
}

ImageLoad::~ImageLoad() {
	delete window;
	cout << "ImageLoad[" << tag << "] DELETED @ " << rank << endl;
}

void ImageLoad::batchProcess() {

	cout << "ImageLoad->BATCHPROCESS [" << tag << "] @ " << rank << endl;

	if (rank == 0) { // rank为0的负责读取分发数据
		memcpy(&window->buffer[window->size], &numImgs, sizeof(int));
		window->size +=sizeof(int);
		for(int n=0;n<numImgs;n++){
			Mat img = imread(fileName+to_string(n)+".jpg",CV_8UC1);
			int RowA = img.rows;
			int Col  = img.cols;
			if(n==0){
				memcpy(&window->buffer[window->size], &RowA, sizeof(int));
				window->size +=sizeof(int);
				memcpy(&window->buffer[window->size], &Col, sizeof(int));
				window->size +=sizeof(int);
			}
			for (int i = 0; i < img.rows; i++)
			{
				for (int j = 0; j < img.cols; j++)
				{
					//at<类型>(i,j)进行操作，对于灰度图
					uchar pixel=img.at<uchar>(i, j);
					memcpy(&window->buffer[window->size], &pixel, sizeof(uchar));
					window->size +=sizeof(uchar);

				}
			}
	
		}
		//  直接将数据发给子顶点，这里没有考虑分布式的数据partition
		int p = 0;
		for (vector<Vertex*>::iterator v = next.begin(); v != next.end();++v) {
			memcpy(sMessages[p]->buffer,&window->buffer[0], window->size);
			sMessages[p]->size = window->size;
			p++;
		}
	
	}
}

void ImageLoad::streamProcess(int channel) {

	//cout << "ImageLoad->STREAMPROCESS [" << tag << "] @ " << rank
	//		<< " IN-CHANNEL " << channel << endl;

	Message* outMessage;

	if (rank == 0) { // one rank to connect to data and partition

		int c = 0;

			// Replicate data to all subsequent vertices
			int n = 0;
			for (vector<Vertex*>::iterator v = next.begin(); v != next.end();
					++v) {

				int start = 0, step = (int) window->size / worldSize,
						messageSize = 0;

				for (int i = 0; i < worldSize; i++) {

					int idx = n * worldSize + i;

					// Use very simple sharding for now (split window into consecutive blocks)
					if (start + step < window->size)
						messageSize = step;
					else
						messageSize = window->size - start;

					outMessage = new Message(messageSize);
					memcpy(outMessage->buffer, &window->buffer[start],
							messageSize);
					outMessage->size = messageSize;
					start += step;

					// Synchronize on outgoing message channel
					pthread_mutex_lock(&senderMutexes[idx]);
					outMessages[idx].push_back(outMessage);

					cout << "BINCONNECTOR->PUSHBACK MESSAGE [" << tag << "] #"
							<< c << " @ " << rank << " OUT-CHANNEL " << idx
							<< " SIZE " << outMessage->size << endl;

					pthread_cond_signal(&senderCondVars[idx]);
					pthread_mutex_unlock(&senderMutexes[idx]);
				}

				n++;

				//sleep(1); // enable this for slow-motion view
			}

			c++;

			//if (c > 20)
			//	return;
	}
}
