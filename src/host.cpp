

#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h> 
#include "cudaCode/sum.cuh"
#include <time.h>
#include<string.h>
#include <stdlib.h>
using namespace std;

int main(){
	clock_t start = clock();

	int nEle = 416000000;
	size_t nBytes = nEle*sizeof(int);
	char * h=new char[nBytes];
	int m =0;int i=0;
	for(i=0;i<nBytes ;i+=4){
		m=rand() % (100-10)+ 10;
		memcpy(h+i, &m, sizeof(int));
	}
	long long sums=sum(h,nBytes);
	double batchlatency = (clock() - start )/ (double) CLOCKS_PER_SEC*1000 ; //batch latency calculation
	cout<<"×ÜÓÃÊ±£º"<<batchlatency<<"s"<<endl;
	cout<<sums;	
	return 0;

}
