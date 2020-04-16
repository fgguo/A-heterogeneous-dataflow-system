#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../usecases/MapReduce.hpp"
#include "../usecases/GpuMR.hpp"
#include "../usecases/GpuMatrixMul.hpp"
using namespace std;

int main(int argc, char* argv[]) {

	Dataflow* dataflow = nullptr;
	bool batchflag = false;
	unsigned long tp = 10000;
	if (argc > 1) {

		if (argc > 2) {
			tp = atol(argv[2]);
		}

		string s(argv[1]);

		 if (s.compare("MR") == 0) {

			dataflow = new MapReduce();
			batchflag = true;

		} 
		else if(s.compare("GpuMR") == 0){
		
		dataflow = new GpuMR();
		batchflag = true;

		}	
		else if(s.compare("GpuMML") == 0){
		
		dataflow = new GpuMatrixMul();
		batchflag = true;

		}	


	} 
	clock_t start, startbatch;
	start = clock();

	// Iterative batch processing (completely synchronized between input windows)
	int i = 0;
	if (batchflag) {

		for (i = 0; i < 1; i++) { //repeat 30x
			startbatch = clock();
			dataflow->batchProcess();
			double batchlatency = (clock() - startbatch)
					/ (double) CLOCKS_PER_SEC * 1000; //batch latency calculation

			cout << "BATCH-" << i + 1 << " COMPLETED IN " << batchlatency
					<< " MSEC (" << batchlatency / 60000 << " MIN) @ "
					<< dataflow->rank << endl;
		}

	} else {

		// Stream processing (asynchronous across input windows)
		dataflow->streamProcess();

	}

	cout << "DATAFLOW COMPLETED IN "
			<< ((clock() - start) / (double) CLOCKS_PER_SEC * 1000) << " MSEC ("
			<< ((clock() - start) / (double) CLOCKS_PER_SEC * 1000) / 60000
			<< " MIN) @ " << dataflow->rank << endl;

	delete dataflow;

	return 0;
}
