#include "Map.hpp"

//#include <pthread/pthread.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <vector>

#include "../communication/Message.hpp"
#include "../function/Function.hpp"
#include "../partitioning/Partition.hpp"
#include "../serialization/Serialization.hpp"
#include "../cudaCode/multi.cuh"
using namespace std;

Map::Map(Function* func, int tag, int rank, int worldSize,bool GPU) :
		Vertex(tag, rank, worldSize,GPU) {
	this->func = func;
	cout << "MAP [" << tag << "] CREATED @ " << rank << endl;
}

Map::~Map() {
	cout << "MAP [" << tag << "] DELETED @ " << rank << endl;
}

void Map::batchProcess() {

	cout << "MAP->BATCHPROCESS [" << tag << "] @ " << rank << endl;

	Serialization ser;
	Partition<int> partitions[previous.size() * worldSize];

	// first process partitions
	if(GPU){
	for (int i = 0; i < previous.size() * worldSize; i++) {
		mul(rMessages[i]->buffer,rMessages[i]->size);
		ser.deserialize(rMessages[i], &partitions[i]);
	}
	}
	else{
	for (int i = 0; i < previous.size() * worldSize; i++) {
		ser.deserialize(rMessages[i], &partitions[i]);
		for (int j = 0; j < partitions[i].size(); j++) {
			partitions[i].set(func->calculate(partitions[i].get(j)), j);
		}
	}
	}

	// then redistribute the data, here includes resharding across channels!
	if (next.size() > 0)
		ser.serialize(partitions, previous.size() * worldSize, sMessages,
				next.size() * worldSize);
}

void Map::streamProcess(int channel) {

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
			for (int j = 0; j < partition.size(); j++) {
				partition.set(func->calculate(partition.get(j)), j);
			}

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
