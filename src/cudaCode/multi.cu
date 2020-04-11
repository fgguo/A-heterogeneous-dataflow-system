#include <cuda_runtime.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <vector>
//#include "../usecases/MapReduce.hpp"
//#include "../communication/Message.hpp"
//#include "../function/Function.hpp"
//#include "../partitioning/Partition.hpp"
//#include "../serialization/Serialization.hpp"

using namespace std;

__global__ void fuc(char *h, const int n){
	  unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;
	 	    if (idx < n)
	    {
		
	    	int value=0;
		memcpy(&value, h+idx *4, sizeof(int));
		value= value*0.01;
		memcpy(h+idx *4, &value, sizeof(int));
	    	    }
}

void cpu(char *h, const size_t n){
	for(int i=0;i<n;i+=4){
		int value=0;
		memcpy(&value, h+i, sizeof(int));
		value= value*0.01;
		memcpy(h+i, &value, sizeof(int));
	}
}

extern "C"
void mul(char *h,size_t nBytes ){
	clock_t start = clock();
	int i=0;
	char *d;
	cudaMalloc((void **)&d, nBytes);	
	cudaMemcpy(d, h, nBytes, cudaMemcpyHostToDevice);
	clock_t copy = clock();
	double copylatency = (copy  - start )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"H2D总用时："<<copylatency<<"s"<<endl;

	int blocksize = 256;
	dim3 block (blocksize, 1);
	dim3 grid  ((nBytes/4 + block.x - 1) / block.x, 1);
	fuc<<<grid, block>>>(d, nBytes /4);
	cudaDeviceSynchronize();
	clock_t process = clock();
	double processlatency = (process - copy )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"kenel总用时："<<processlatency <<"s"<<endl;

	cudaMemcpy(h, d, nBytes, cudaMemcpyDeviceToHost);
	cout<<endl;
	clock_t DTH = clock();
	double DTHlatency = (DTH  - process )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"DTH 总用时："<<DTHlatency <<"s"<<endl;
	double batchlatency = (clock() - start )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"GPU总用时："<<batchlatency<<"s"<<endl;
}
