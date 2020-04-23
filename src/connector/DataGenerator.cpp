#include "DataGenerator.hpp"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#include "../communication/Message.hpp"
#include "../communication/Window.hpp"

using namespace std;

DataGenerator::DataGenerator(int tag, int rank, int worldSize,bool GPU) :
		Vertex(tag, rank, worldSize,GPU) {
	this->window = new Window(WINDOW_SIZE);
	cout << "DataGenerator[" << tag << "] CREATED @ "
			<< rank << endl;
}

DataGenerator::~DataGenerator() {
	delete window;
	cout << "DataGenerator[" << tag << "] DELETED @ " << rank << endl;
}

void DataGenerator::batchProcess() {

	cout << "DataGenerator->BATCHPROCESS [" << tag << "] @ " << rank << endl;

	if (rank == 0) { // one rank to connect to data and partition
	//int nRow = 1 << 13,nCol = 1 << 13;
	int RowA=1; 
	int Col = 128*128 ;
	int ColB = 512 ;
	memcpy(&window->buffer[window->size], &RowA, sizeof(int));
	window->size +=sizeof(int);
	memcpy(&window->buffer[window->size], &Col, sizeof(int));
	window->size +=sizeof(int);
	memcpy(&window->buffer[window->size], &ColB , sizeof(int));
	window->size +=sizeof(int);
	for(int i=0;i<RowA;i++){
		for(int j=0;j<Col;j++){
			double value= 1;
			memcpy(&window->buffer[window->size], &value, sizeof(double));
			window->size +=sizeof(double);
		}
	}

	for(int i=0;i<Col;i++){
		for(int j=0;j<ColB;j++){
			double value= 1;
			memcpy(&window->buffer[window->size], &value, sizeof(double));
			window->size +=sizeof(double);

		}
	}
	
	
			//  直接将数据发给子顶点
			int p = 0;
			for (vector<Vertex*>::iterator v = next.begin(); v != next.end();++v) {
				memcpy(sMessages[p]->buffer,&window->buffer[0], window->size);
				sMessages[p]->size = window->size;
				p++;
			}
	}
}

void DataGenerator::streamProcess(int channel) {

	//cout << "BINCONNECTOR->STREAMPROCESS [" << tag << "] @ " << rank
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
