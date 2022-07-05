#include <stdio.h>  
#include <stdlib.h>  
//#include "kernel.cu"  

#define N 256
extern "C" void addKernel(void);

int main(int argc)
{
	printf("Hello World from GPU!\n");
	addKernel();
	
}