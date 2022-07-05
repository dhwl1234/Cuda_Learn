#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>
//#include "kernel.cu"  

#define N 256
extern "C" void addKernel(int* a, int* b, int* c, int size);

void initialData(int* ip, int size)
{
	//对数组进行随机赋值
	time_t t;
	srand((unsigned int)time(&t));
	for (int i = 0; i < size; i++)
	{
		ip[i] = (int)(rand() & 0xFF) / 10.0f;
	}
}


int main(int argc, char** argv)
{

	int nElem = 1024;
	size_t nBytes = nElem * sizeof(int);
	int* h_A, * h_B, * h_C;
	h_A = (int*)malloc(nBytes);
	h_B = (int*)malloc(nBytes);
	h_C = (int*)malloc(nBytes);

	initialData(h_A, nElem);
	initialData(h_B, nElem);
	initialData(h_C,nElem);

	
	addKernel(h_A, h_B, h_C, nElem);
	for (int i = 0; i < N; i++)
	{
		printf("%d is %d.\n", i, h_C[i]);
	}
	return 0;
}