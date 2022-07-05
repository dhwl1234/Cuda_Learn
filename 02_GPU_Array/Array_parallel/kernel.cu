#include "cuda_runtime.h"  
#include "device_launch_parameters.h"  

__global__ void Parallel(const int* a, const int* b, int* c)
{
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	c[i] = b[i] + a[i];
}

extern "C" void addKernel(const int* h_a, const int* h_b, int* h_c, int size)
{
	int* d_A, * d_B, * d_C;
	cudaSetDevice(0);
	cudaMalloc((void**)&d_A,  size);
	cudaMalloc((void**)&d_B,  size);
	cudaMalloc((void**)&d_C,  size);
	cudaMemcpy(d_A, h_a,  size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_b,  size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_C, h_c,  size, cudaMemcpyHostToDevice);

	Parallel << <2, 128 >> > (d_A, d_B, d_C);

	cudaMemcpy(h_c, d_C, size , cudaMemcpyDeviceToHost);

	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}