#include <unistd.h>
#include <iostream>
#include <stdio.h> 
#include "cudaCode/MatrixMul.cuh"
#include <time.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


#include <iostream>
using namespace std;
 
void MatrixMulOnHost(int m, int n, int k, float* A, float* B, float* C)
{
    for (int Row = 0; Row < m; ++ Row)
		for (int Col = 0; Col < k; ++ Col )
		{
			float sum = 0;
			for (int i = 0; i < n; ++i)
			{
				float a = A[Row * n + i];
				float b = B[Col + i * k];
				sum += a * b;
			}
			C[Row* k + Col] = sum;
		}
}
 
int main()
{
	MatrixMul();
  
}

