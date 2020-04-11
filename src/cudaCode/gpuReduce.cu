#include <cuda_runtime.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h> 
#include <time.h>
//#include "../usecases/MapReduce.hpp"
//#include "../communication/Message.hpp"
//#include "../function/Function.hpp"
//#include "../partitioning/Partition.hpp"
//#include "../serialization/Serialization.hpp"

using namespace std;

__global__ void sum(char *g_idata, long long *g_odata, unsigned int n)
{
    // set thread ID
    unsigned int tid = threadIdx.x;
    unsigned int idx = 4*(blockIdx.x * blockDim.x + threadIdx.x);
    // convert global data pointer to the local pointer of this block
    char *idata = g_idata + 4*(blockIdx.x * blockDim.x);

    // boundary check
    if(idx >= n) return;
    long long v1,v2,v3;
    // in-place reduction in global memory
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1)
    {
        if (tid < stride)
        {
	    memcpy(&v1, idata+tid*4, sizeof(int));
	    memcpy(&v2, idata+(tid+stride)*4, sizeof(int));
	    v3 = v1+v2;
	    //printf("%d,%d,%d \n", v1,v2,v3);
	    memcpy(idata+tid*4,&v3,sizeof(int));
            //idata[tid] += idata[tid + stride];
        }

        __syncthreads();
    }
    // write result for this block to global mem
    if (tid == 0) 
	memcpy(g_odata+blockIdx.x,idata,sizeof(int));
}

long long cpu(char *h, const size_t n){
	long long sum=0;
	for(int i=0;i<n;i+=4){
		int value=0;
		memcpy(&value, h+i, sizeof(int));
		sum+= value;
	}
	return sum;
}


int main(){
	clock_t start = clock();
	int nEle = 416000000;
	size_t nBytes = nEle*sizeof(int);
	int i=0;
	char * h,*d;
        long long *g_result;
	h=(char *)malloc(nBytes);
	cudaMalloc((void **)&d, nBytes);
	g_result=(long long *)malloc(nBytes);
	int m =0;
	for(i=0;i<nBytes ;i+=4){
		m=rand() % (100-10)+ 10;
		memcpy(h+i, &m, sizeof(int));
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
	cout<<cpu(h,nBytes )<<endl;
	clock_t cpu = clock();
	double cpulatency = (cpu  - v2arr )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"CPU总用时："<<cpulatency <<"ms"<<endl;
	v2arr = clock();
	translatency = (v2arr  - cpu )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"转数组总用时："<<translatency<<"ms"<<endl;

	cudaMemcpy(d, h, nBytes, cudaMemcpyHostToDevice);
	clock_t copy = clock();
	double copylatency = (copy  - v2arr )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"H2D总用时："<<copylatency<<"ms"<<endl;

	int blocksize = 256;
	dim3 block (blocksize, 1);
	dim3 grid  ((nEle + block.x - 1) / block.x, 1);
	long long *d_odata ;
        cudaMalloc((void **) &d_odata, grid.x * sizeof(long long));
	sum<<<grid, block>>>(d,d_odata, nBytes );
	cudaDeviceSynchronize();
	clock_t process = clock();
	double processlatency = (process - copy )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"kenel总用时："<<processlatency <<"ms"<<endl;

	cudaMemcpy(g_result, d_odata, grid.x * sizeof(long long), cudaMemcpyDeviceToHost);
	long long gpu_sum = 0;
	
        for (int i = 0; i < grid.x; i++){
		gpu_sum+=g_result[i];
		}
	cout<<gpu_sum<<endl;
	clock_t DTH = clock();
	double DTHlatency = (DTH  - process )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"DTH 总用时："<<DTHlatency <<"ms"<<endl;

	double batchlatency = (clock() - start )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"GPU总用时："<<batchlatency<<"ms"<<endl;

	return 0;

}
