# CUDA编程注意点

## CUDA编程结构

一个典型的CUDA编程结构包括5个步骤

1. 分配GPU内存
2. 从CPU内存中拷贝数据到GPU内存
3. 调用CUDA内核函数来完成程序指定的运算
4. 将数据拷贝回CPU内存
5. 释放GPU内存空间



## CUDA在Windows中编程的注意事项

​		cuda在vsstudio编程时，由于编译器编译的是C++代码，因此需要分两个文件编写，否则在调用内核函数时<<<>>>该符号会与c++中的<<冲突并且出错，本人参考教程，做法如下：

​		在VSstudio中新建CUDA项目后，会生成一个Kernel.cu的文件，初始该文件中内置了DEMO，将文件代码清空，从而编写自己的项目代码，在该文件中进行CUDA编程。再新建一个main函数，用于调用.cu文件

```c++
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
```

```c++
#include "cuda_runtime.h"  
#include "device_launch_parameters.h"  
#include<stdio.h>
__global__ void helloFromGPU(void)
{
	printf("Hello World from GPU!\n");
}

extern "C" void addKernel(void)
{

	helloFromGPU << <1, 10 >> > ();
	cudaDeviceReset();
}
```

在上述程序中，只用到了第三步，调用内核。\_\_global__ 作用是告诉编译器这个函数将从CPU中调用，然后在GPU上执行，用helloFromGPU << <1, 10 >> > ();这行命令启动内核函数。

