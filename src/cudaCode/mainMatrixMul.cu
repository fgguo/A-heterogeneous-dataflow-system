// CUDA runtime �� + CUBLAS ��
#include "cuda_runtime.h"
#include "cublas_v2.h"
#include <iostream>
#include <stdlib.h>
#include "MatrixMul.cuh"
using namespace std;

// ������Ծ����ά��
int const A_ROW = 8192 ;
int const A_COL = 8192 ;
int const B_ROW = 8192 ;
int const B_COL = 8192 ;

extern "C"
void MatrixMul()
{
  // ����״̬����
  cublasStatus_t status;
  float *h_A,*h_B,*h_C;   //�洢���ڴ��еľ���
  h_A = (float*)malloc(sizeof(float)*A_ROW*A_COL);  //���ڴ��п��ٿռ�
  h_B = (float*)malloc(sizeof(float)*B_ROW*B_COL);
  h_C = (float*)malloc(sizeof(float)*A_ROW*B_COL);

  // Ϊ����������Ԫ�ظ��� 0-10 ��Χ�ڵ������
  for (int i=0; i<A_ROW*A_COL; i++) {
    h_A[i] = (float)(rand()%10+1);
  }
  for(int i=0;i<B_ROW*B_COL; i++) {
    h_B[i] = (float)(rand()%10+1);
  }
  // ��ӡ�����Եľ���
  cout << "���� A :" << endl;
  for (int i=0; i<A_ROW*A_COL; i++){
    cout << h_A[i] << " ";
    if ((i+1)%A_COL == 0) cout << endl;
  }
  cout << endl;
  cout << "���� B :" << endl;
  for (int i=0; i<B_ROW*B_COL; i++){
    cout << h_B[i] << " ";
    if ((i+1)%B_COL == 0) cout << endl;
  }
  cout << endl;

  float *d_A,*d_B,*d_C;    //�洢���Դ��еľ���
  cudaMalloc((void**)&d_A,sizeof(float)*A_ROW*A_COL); //���Դ��п��ٿռ�
  cudaMalloc((void**)&d_B,sizeof(float)*B_ROW*B_COL);
  cudaMalloc((void**)&d_C,sizeof(float)*A_ROW*B_COL);

  cublasHandle_t handle;
  cublasCreate(&handle);
  cudaMemcpy(d_A,h_A,sizeof(float)*A_ROW*A_COL,cudaMemcpyHostToDevice); //���ݴ��ڴ濽�����Դ�
  cudaMemcpy(d_B,h_B,sizeof(float)*B_ROW*B_COL,cudaMemcpyHostToDevice);

  float a = 1, b = 0;
  cublasSgemm(
          handle,
          CUBLAS_OP_N,   //����A�����Բ�������ת�ã���������
          CUBLAS_OP_N,   //����B�����Բ�������ת�ã���������
          B_COL,          //����B^T��C^T������
          A_ROW,          //����A^T��C^T������
          B_ROW,          //B^T��������A^T���������˴�Ҳ��ΪA_COL,һ����
          &a,             //alpha��ֵ
          d_B,            //�����ΪB^T
          B_COL,          //B^T��leading dimension���������ȣ���leading dimensionΪB^T������(B������)
          d_A,            //�Ҿ���ΪA^T
          A_COL,          //A^T��leading dimension���������ȣ���leading dimensionΪA^T������(A������)
          &b,             //beta��ֵ
          d_C,            //�������C
          B_COL           //C^T��leading dimension��C^T����һ���������ȣ���leading dimensionΪC^T������(C������)
  );
  //��ʱ�õ��Ľ������C=AB,������C�ǰ������ȣ��ʴ�ʱ�õ���CӦ������ȷ�����ת��
  std::cout << "��������ת�� ( (A*B)��ת�� )��" << std::endl;


  cudaMemcpy(h_C,d_C,sizeof(float)*A_ROW*B_COL,cudaMemcpyDeviceToHost);
  for(int i=0;i<A_ROW*B_COL;++i) {
    std::cout<<h_C[i]<<" ";
    if((i+1)%B_COL==0) std::cout<<std::endl;
  }
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
  free(h_A);
  free(h_B);
  free(h_C);
}