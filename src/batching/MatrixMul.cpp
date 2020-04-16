/*

By Fu Guo
2020 4.16

*/

#include "MatrixMul.hpp"

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h> 
#include "../communication/Message.hpp"
#include "../partitioning/Partition.hpp"
#include "../serialization/Serialization.hpp"
#include "../cudaCode/MatrixMul.cuh"
using namespace std;

MatrixMul::MatrixMul(int tag, int rank, int worldSize,bool GPU) :
		Vertex(tag, rank, worldSize,GPU) {
	cout << "MatrixMul[" << tag << "] CREATED @ " << rank << endl;
}

MatrixMul::~MatrixMul() {
	cout << "MatrixMul[" << tag << "] DELETED @ " << rank << endl;
}

void MatrixMul::batchProcess() {

	cout << "MatrixMul->BATCHPROCESS [" << tag << "] @ " << rank << endl;

	Serialization ser;
	Partition<int> partitions[previous.size() * worldSize];

	// first process partitions
	if(GPU){
		for (int i = 0; i < previous.size() * worldSize; i++) {
			matrixmul(rMessages[i]->buffer);
			int RowA=0; 
			int ColB = 0;//获取矩阵形状
			rMessages[i]->size=3*sizeof(int)+RowA*ColB*sizeof(double);
			for(int j=0;j<next.size();j++){
				memcpy(&sMessages[j]->buffer[sMessages[j]->size], rMessages[i]->buffer,rMessages[i]->size);
				sMessages[j]->size=rMessages[i]->size;
			}
		}
	}
	else{
		for (int i = 0; i < previous.size() * worldSize; i++) {
			CpuMatriMul(rMessages[i]->buffer);
			int RowA=0; 
			int ColB = 0;//获取矩阵形状
			rMessages[i]->size=3*sizeof(int)+RowA*ColB*sizeof(double);
			for(int j=0;j<next.size();j++){
				memcpy(&sMessages[j]->buffer[sMessages[j]->size], rMessages[i]->buffer,rMessages[i]->size);
				sMessages[j]->size=rMessages[i]->size;
			}

		}
	}

}

void MatrixMul::streamProcess(int channel) {

	//cout << "MAP->STREAMPROCESS [" << tag << "] @ " << rank << " IN-CHANNEL "
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
