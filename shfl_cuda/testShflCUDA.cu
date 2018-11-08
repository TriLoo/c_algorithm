/**
 * @author smh
 * @date 2018.11.06
 *
 * @brief test Shfl instruction in CUDA.
 */

#include "testShflCUDA.h"
#include <iostream>

using namespace std;

__global__ void bcast(int arg)
{
    // 这里可以看出来，一个warp是对应于同一个block而言的，因为threadIdx对不同的block是独立的
    int laneId = threadIdx.x & 0x1f;   // 等价于对32取余，即只保留低5位，高位被强制置零
    int value;
    if(laneId == 0)                    // 每个warp的第一个thread
        value = arg;

    // 也就是说，__shfl指令返回的是源thread中var变量的值
    value = __shfl(value, 0);          // shfl return a 4-byte word referenced by var from the source lane ID as an unsigned integer.
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
        else  // 当laneId超过warpSize的范围(小于0或大于warpSize参数)时，返回的值就是源lane的value值
            printf("thread %d the returned value is: %d \n", threadIdx.x, n);  // 返回的结果就是源laneId的value值
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
        // 这里以butterfly addression pattern 的方式实现了32个线程(warp)内的Reduction
        // butterfly addression pattern的stride从i=16, 8, 4, 2, 1递减的，最后的结果就是全局Reduction，且warp里面各个线程的计算结果都是相同的。
		value += __shfl_xor(value, i, 32);  // calculate a source line ID by performing a bitwise XOR of the caller's lane ID with laneMask: the value of var held by the resulting (source) lane ID is returned.

	printf("Thread %d final value = %d \n", threadIdx.x, value);
}

void testShfl::testShflKernel()
{
    // 输入的数据是2个矩阵，每个矩阵的尺寸为16行32列
    float *data_d, *data_h = new float[32 * 32];  // 32 * 16 * 2
    float *data_out_h = new float [32 * 32];
    for (int i = 0; i < 32 * 32; ++i)
        data_h[i] = i;
    /**
    for (int i = 0; i < 16; ++i)    // 行
        for (int j = 0; j < 32; ++j)  // 列
        {
            int idx = i * 32 + j;
            data_h[idx] = 0;
        }
    for (int i = 0; i < 16; ++i)    // 行
        for (int j = 0; j < 32; ++j)  // 列
        {
            int idx = i * 32 + j;
            data_h[idx] = 1;
        }
    */

    cudaError_t cudaStatus = cudaSuccess;
    size_t d_pitch = 0;
    cudaStatus = cudaMallocPitch(&data_d, &d_pitch, 32, 32);
    assert(cudaStatus == cudaSuccess);
    cudaStatus = cudaMemcpy2D(data_d, d_pitch, data_h, 32 * sizeof(float), 32 * sizeof(float), 32, cudaMemcpyHostToDevice);
    assert(cudaStatus == cudaSuccess);

    dim3 blockPerGrid(2, 1, 1);
    dim3 threadPerBlock(32 * 16, 1, 1);
    //testShule<<<blockPerGrid, threadPerBlock>>>(data_d, data_h);
    //bcast<<<1, 32>>>(1234);
    //testShfl_scan4<<<1, 32>>>();
    testShfl_warpReduce<<<1, 32>>>();
    cudaDeviceSynchronize();
    cout << cudaGetErrorString(cudaPeekAtLastError()) << endl;

    cudaStatus = cudaMemcpy2D(data_out_h, 32 * sizeof(float), data_d, d_pitch, 32 * sizeof(float), 32, cudaMemcpyDeviceToHost);
    assert(cudaStatus == cudaSuccess);

    cudaStatus = cudaFree(data_d);
    assert(cudaStatus == cudaSuccess);

    delete [] data_h;
    delete [] data_out_h;

}

