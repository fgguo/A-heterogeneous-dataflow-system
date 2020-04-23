#include <stdio.h>
#include <cuda_runtime.h>
#include <iostream>
using namespace std;
template <size_t BLOCK_SIZE>
void __global__ MatMatMul(double *A,double *B,double *C,size_t m,size_t n,size_t p)
{
    
    double Cvalue = 0;  
    int row = blockIdx.y * blockDim.y + threadIdx.y;  
    int col = blockIdx.x * blockDim.x + threadIdx.x;  
    if(row<m&&col<p){
        for (int e = 0; e < n; ++e){
    		Cvalue += A[row * n+ e]* B[e * p+ col];  
    	}
       	C[row * p+ col] = Cvalue;
    }
}

extern "C"
void CpuMatriMul(char * h){
  	clock_t start = clock();
	int RowA=0; 
	int Col = 0;
	int ColB = 0;
	//获取矩阵形状
	memcpy(&RowA, h, sizeof(int));
	memcpy(&Col, h+sizeof(int), sizeof(int));
	memcpy(&ColB, h+2*sizeof(int), sizeof(int));
	//申请内存
	double *h_A,*h_B,*h_C;
	cudaHostAlloc(&h_A,sizeof(double) * RowA* Col,cudaHostAllocWriteCombined);
	cudaHostAlloc(&h_B,sizeof(double) * Col * ColB ,cudaHostAllocWriteCombined);
	cudaHostAlloc(&h_C,sizeof(double) * RowA * ColB ,cudaHostAllocWriteCombined);
	//h_A=(double *)malloc(RowA*Col*sizeof(double ));
	//h_B=(double *)malloc(ColB*Col*sizeof(double ));
	//h_C=(double *)malloc(RowA*ColB*sizeof(double ));
	char * h_a = h+3*sizeof(int);//A数组起始地址
	char * h_b = h_a+RowA*Col*sizeof(double);   //B数组起始地址
	//从字符数组copy到double数组
	for(int i=0;i<RowA*Col;i++){
		memcpy(h_A+i, h_a+i*sizeof(double),sizeof(double));
	}
	for(int i=0;i<ColB*Col;i++){
		memcpy(h_B+i, h_b+i*sizeof(double),sizeof(double));
	}	
	cout<<RowA<<Col<<ColB<<endl ;
	//CPU版本
	clock_t cpustart  = clock();
   	for (int r = 0; r < RowA; r++) {
        	for (int c = 0; c < ColB; c++) {
            		for (int e = 0; e < Col; e++) {
                		h_C[r*ColB+ c] += h_A[r*Col+e] * h_B[e*ColB+c]; 
           		}
        	}
    	}
	
	clock_t cpuend  = clock();
	memcpy(h,&RowA,sizeof(int));
	memcpy(h+sizeof(int),&ColB,sizeof(int));
	h_a = h+2*sizeof(int);//A数组起始地址
	for(int i=0;i<RowA*ColB;i++){
		memcpy(h_a+i*sizeof(double), h_C+i,sizeof(double));
	}
	cudaFreeHost(h_A);
	cudaFreeHost(h_B);
	cudaFreeHost(h_C);

	double cpulatency = (cpuend   - cpustart  )/ (double) CLOCKS_PER_SEC*1000 ;
	cout<<"CPU总用时："<<cpulatency <<"ms"<<endl;
}

extern "C"
void matrixmul(char * h)
{
	clock_t start = clock();
	int RowA=0; 
	int Col = 0;
	int ColB = 0;
	//获取矩阵形状
	memcpy(&RowA, h, sizeof(int));
	memcpy(&Col, h+sizeof(int), sizeof(int));
	memcpy(&ColB, h+2*sizeof(int), sizeof(int));
	//申请内存
	double *h_A,*h_B,*h_C,*d_A,*d_B,*d_C;
	cudaHostAlloc(&h_A,sizeof(double) * RowA* Col,cudaHostAllocWriteCombined);
	cudaHostAlloc(&h_B,sizeof(double) * Col * ColB ,cudaHostAllocWriteCombined);
	cudaHostAlloc(&h_C,sizeof(double) * RowA * ColB ,cudaHostAllocWriteCombined);
	cudaMalloc(&d_A,sizeof(double) * RowA* Col  );
	cudaMalloc(&d_B,sizeof(double) * Col * ColB );
	cudaMalloc(&d_C,sizeof(double) * RowA* ColB );
	//h_A=(double *)malloc(RowA*Col*sizeof(double ));
	//h_B=(double *)malloc(ColB*Col*sizeof(double ));
	//h_C=(double *)malloc(RowA*ColB*sizeof(double ));
	char * h_a = h+3*sizeof(int);//A数组起始地址
	char * h_b = h_a+RowA*Col*sizeof(double);   //B数组起始地址
	int count=0;
	//从字符数组copy到double数组
	for(int i=0;i<RowA*Col;i++){
		memcpy(h_A+i, h_a+i*sizeof(double),sizeof(double));
	}
	for(int i=0;i<ColB*Col;i++){
		memcpy(h_B+i, h_b+i*sizeof(double),sizeof(double));
	}	
	cout<<RowA<<Col<<ColB<<endl ;
	cudaMemcpy(d_A,h_A,sizeof(double) * RowA* Col ,cudaMemcpyHostToDevice);
	cudaMemcpy(d_B,h_B,sizeof(double) * Col * ColB ,cudaMemcpyHostToDevice);
	cudaFreeHost(h_A);
	cudaFreeHost(h_B);
	const dim3 gridDim((ColB+ 16- 1) / 16, (RowA+ 16- 1) / 16),blockDim(16, 16);

	MatMatMul<16><<<gridDim, blockDim>>>(d_A, d_B, d_C, RowA, Col, ColB);  
	cudaDeviceSynchronize();
	cudaMemcpy(h_C, d_C, ColB*RowA*sizeof(double), cudaMemcpyDeviceToHost);
	memcpy(h,&RowA,sizeof(int));
	memcpy(h+sizeof(int),&ColB,sizeof(int));
	h_a = h+2*sizeof(int);//A数组起始地址
	for(int i=0;i<RowA*ColB;i++){
		memcpy(h_a+i*sizeof(double), h_C+i,sizeof(double));
	}
	cudaFreeHost(h_C);
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	double batchlatency = (clock() - start )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"GPU总用时："<<batchlatency<<"ms"<<endl;

}