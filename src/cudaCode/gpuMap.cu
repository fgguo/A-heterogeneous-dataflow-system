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
		value= value*0.1;
		memcpy(h+idx *4, &value, sizeof(int));
	    	    }
}

void cpu(char *h, const size_t n){
	for(int i=0;i<n;i+=4){
		int value=0;
		memcpy(&value, h+i, sizeof(int));
		value= value*0.1;
		memcpy(h+i, &value, sizeof(int));
	}
}


int main(){
	clock_t start = clock();
	int nEle = 416000000;
	size_t nBytes = nEle*sizeof(int);
	int i=0;
	char * h,*d,*g_result;
	h=(char *)malloc(nBytes);
	cudaMalloc((void **)&d, nBytes);
	g_result=(char *)malloc(nBytes);
	for(i=0;i<nBytes ;i+=4){
		memcpy(h+i, &i, sizeof(int));
	}
	cout<<endl;
	//for(i=0;i<nBytes ;i+=4){
	//	int value=0;
	//	memcpy(&value, h+i, sizeof(int));
	//	
	//}
	cout<<endl;
	cout<<endl;

	clock_t v2arr = clock();
	double translatency = (v2arr  - start )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"转数组总用时："<<translatency<<"s"<<endl;
	cpu(h,nEle);
	clock_t cpu = clock();
	double cpulatency = (cpu  - v2arr )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"CPU总用时："<<cpulatency <<"s"<<endl;
	for(i=0;i<416 ;i+=4){
		int value=0;
		memcpy(&value, h+i, sizeof(int));
		cout<<value;
	}
	
	for(i=0;i<nBytes ;i+=4){
		memcpy(h+i, &i, sizeof(int));
	}
	cout<<endl;	v2arr = clock();
	translatency = (v2arr  - cpu )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"转数组总用时："<<translatency<<"s"<<endl;

	cudaMemcpy(d, h, nBytes, cudaMemcpyHostToDevice);
	clock_t copy = clock();
	double copylatency = (copy  - v2arr )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"H2D总用时："<<copylatency<<"s"<<endl;

	int blocksize = 256;
	dim3 block (blocksize, 1);
	dim3 grid  ((nEle + block.x - 1) / block.x, 1);
	fuc<<<grid, block>>>(d, nEle);
	cudaDeviceSynchronize();
	clock_t process = clock();
	double processlatency = (process - copy )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"kenel总用时："<<processlatency <<"s"<<endl;

	cudaMemcpy(g_result, d, nBytes, cudaMemcpyDeviceToHost);
	for(i=0;i<416 ;i+=4){
		int value=0;
		memcpy(&value, g_result+i, sizeof(int));
		cout<<value;
	}
	cout<<endl;
	clock_t DTH = clock();
	double DTHlatency = (DTH  - process )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"DTH 总用时："<<DTHlatency <<"s"<<endl;

	double batchlatency = (clock() - start )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"GPU总用时："<<batchlatency<<"s"<<endl;

	return 0;

}
