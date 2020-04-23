/*
Resize.cpp
By Fu Guo
2020 4.19
*/
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
#include "Resize.hpp"
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h> 
#include "../communication/Message.hpp"
#include "../partitioning/Partition.hpp"
#include "../serialization/Serialization.hpp"
#include "../cudaCode/MatrixMul.cuh"

using namespace cv;
using namespace std;

Resize::Resize(int tag, int rank, int worldSize,bool GPU,int width,int height) :
		Vertex(tag, rank, worldSize,GPU) {
	this->width=width;
	this->height=height;
	this->window = new Window(WINDOW_SIZE);
	cout << "Resize[" << tag << "] CREATED @ " << rank << endl;
}

Resize::~Resize() {
	delete window;
	cout << "Resize[" << tag << "] DELETED @ " << rank << endl;
}

void Resize::batchProcess() {

	cout << "Resize->BATCHPROCESS [" << tag << "] @ " << rank << endl;
	if(GPU){
		cout<<"have not realize!"<<endl;
	}
	else{
		for (int i = 0; i < previous.size() * worldSize; i++) {
			int numImgs=0;
			int RowA=0; 
			int Col = 0;
			//获取矩阵形状
			memcpy(&numImgs, rMessages[i]->buffer, sizeof(int));
			memcpy(&RowA, rMessages[i]->buffer+sizeof(int), sizeof(int));
			memcpy(&Col, rMessages[i]->buffer+2*sizeof(int), sizeof(int));
			cout<<"numImgs:"<<numImgs<<"imgSize:"<<RowA<<"×"<<Col<<endl;
			//赋值新矩阵信息
			memcpy(rMessages[i]->buffer+sizeof(int), &height, sizeof(int));
			memcpy(rMessages[i]->buffer+2*sizeof(int), &width, sizeof(int));
		
			char * imgMat = rMessages[i]->buffer+3*sizeof(int);//图像数组起始地址
			uchar pixel = 0;
			for(int n=0;n<numImgs;n++){
				Mat img(RowA, Col, CV_8UC1);//opencv中保存图像信息的矩阵
				for(int i = 0; i < RowA; i++)
           				for(int j = 0; j < Col; j++){	
                   				memcpy(&pixel, imgMat+n*RowA*Col+(i*Col+j)*sizeof(uchar), sizeof(uchar));
						img.at<uchar >(i,j)=pixel;
					}
				
				resize(img, img, Size(height, width));//调用opencv提供的resize函数
				for (int i = 0; i < height; i++){
					for (int j = 0; j < width; j++){
						//将resize后的图像信息保存至window中，传给子顶点。
						pixel=img.at<uchar>(i, j);
						memcpy(imgMat+n*width*height+(i*width+j)*sizeof(uchar), &pixel, sizeof(uchar));
					}
				}
			}
			rMessages[i]->size=3*sizeof(int)+numImgs*width*height*sizeof(uchar);
			//将数据传给子顶点
			for(int j=0;j<next.size();j++){
				memcpy(&sMessages[j]->buffer[sMessages[j]->size], rMessages[i]->buffer,rMessages[i]->size);
				sMessages[j]->size=rMessages[i]->size;
			}

		}
	}

}

void Resize::streamProcess(int channel) {

	//cout << "Resize->STREAMPROCESS [" << tag << "] @ " << rank << " IN-CHANNEL "
	//		<< channel << endl;

	Message* inMessage, *outMessage;
	list<Message*>* tmpMessages = new list<Message*>();

	int c = 0;
	bool doProcess = true;
	while (doProcess) {

		// Synchronize on incoming message channel
		pthread_mutex_lock(&listenerMutexes[channel]);

		while (inMessages[channel].empty())
			pthread_cond_wait(&listenerCondVars[channel],
					&listenerMutexes[channel]);

		while (!inMessages[channel].empty()) {

			inMessage = inMessages[channel].front();
			inMessages[channel].pop_front();

			//cout << "MAP->POP MESSAGE [" << tag << "] #" << c << " @ " << rank
			//		<< " IN-CHANNEL " << channel << " SIZE " << inMessage->size
			//		<< endl;

			tmpMessages->push_back(inMessage);
		}

		pthread_mutex_unlock(&listenerMutexes[channel]);

		while (!tmpMessages->empty()) {

			inMessage = tmpMessages->front();
			tmpMessages->pop_front();

			Partition<int> partition;
			Serialization ser;

			ser.deserialize(inMessage, &partition);

			// Replicate data to all subsequent vertices, do not actually reshard the data here
			int n = 0;
			for (vector<Vertex*>::iterator v = next.begin(); v != next.end();
					++v) {

				outMessage = new Message();
				ser.serialize(&partition, outMessage);

				int idx = n * worldSize + rank; // always keep workload on same rank for Map

				if (PIPELINE) {

					// Pipeline mode: immediately copy message into next operator's queue
					pthread_mutex_lock(&(*v)->listenerMutexes[idx]);
					(*v)->inMessages[idx].push_back(outMessage);

					cout << "MAP->PIPELINE MESSAGE [" << tag << "] #" << c
							<< " @ " << rank << " IN-CHANNEL " << channel
							<< " OUT-CHANNEL " << idx << " SIZE "
							<< outMessage->size << " CAP "
							<< outMessage->capacity << endl;

					pthread_cond_signal(&(*v)->listenerCondVars[idx]);
					pthread_mutex_unlock(&(*v)->listenerMutexes[idx]);

				} else {

					// Normal mode: synchronize on outgoing message channel & send message
					pthread_mutex_lock(&senderMutexes[idx]);
					outMessages[idx].push_back(outMessage);

					cout << "MAP->PUSHBACK MESSAGE [" << tag << "] #" << c
							<< " @ " << rank << " IN-CHANNEL " << channel
							<< " OUT-CHANNEL " << idx << " SIZE "
							<< outMessage->size << " CAP "
							<< outMessage->capacity << endl;

					pthread_cond_signal(&senderCondVars[idx]);
					pthread_mutex_unlock(&senderMutexes[idx]);
				}

				n++;
			}

			delete inMessage; // delete incoming message and free memory
			c++;
		}

		tmpMessages->clear();
	}

	delete tmpMessages; // delete temp message buffer
}
