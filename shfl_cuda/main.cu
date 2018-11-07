#include <iostream>
#include <cuda.h>
#include <cuda_runtime.h>

#include <stdio.h>

__global__ void testShfl(int arg)
{
	int laneIdx = threadIdx.x & 0x1F;

	int value = 0;
	if(laneIdx == 0)
		value = arg;

	value = __shfl(value, 0);  // return the 4-byte word referenced by var from the source lane ID as an unsigned integer.
	if(value != arg)
		printf("Thread %d failed.\n", threadIdx.x);
}

__global__ void testShfl_scan4()
{
	int laneId = threadIdx.x & 0x1F;     // caller's lane ID

	int value = 31 - laneId;

	for(int i = 1; i <= 4; i *= 2)
	{
		// 这里的n就是从源lane中value的数值
		// 这里使用__shfl_up实现了从左到右的scan4s算法
		// 使用_shfl_down实现从右到左的scane4算法
		int n = __shfl_up(value, i, 8);   // return the value of var held by the resulting lane ID！lower delta lanes will be unchanged.
		if(laneId >= i)
			value += n;
	}

	printf("Thread %d final value = %d \n", threadIdx.x, value);
}

// reduction across a warp
__global__ void testShfl_warpReduce()
{
	int laneId = threadIdx.x & 0x1F;

	int value = 31 - laneId;

	// use XOR mode to perform butterfly reduction
	for(int i = 16; i >= 1; i/=2)
		value += __shfl_xor(value, i, 32);  // calculate a source line ID by performing a bitwise XOR of the caller's lane ID with laneMask: the value of var held by the resulting (source) lane ID is returned.

	printf("Thread %d final value = %d \n", threadIdx.x, value);
}


using namespace std;

int main()
{
	//testShfl<<<1, 32>>>(1234);
	testShfl_warpReduce<<<1, 32>>>();

	cudaDeviceSynchronize();
	cout << cudaGetErrorString(cudaPeekAtLastError()) << endl;

	return 0;
}
