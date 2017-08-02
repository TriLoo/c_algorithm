#include <iostream>
#include <cassert>

/* ******************
 * Author : smher
 * Data   : 2017. 08. 01
 * Description :
 * 		This file implement the all-prefix-sums (scan) algorithm parallel. based on "GPU Gem 3" chapter 39.
 *
 * 		The Version 2 ( Up Sweep and Down Sweep cannot be fit to not power of 2 lenght array !!!
 *
 * 		TODO:
 * 		    There is a lot of room for optimization as for Versioin 2 !!!
 */

#define SIZE 128
//#define SIZE 127   // Not fit for Version 2

using namespace std;

//__device__ void UpSweep(float *data, int width)
__global__ void UpSweep(float *data, int width)
{
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int idy = threadIdx.y + blockIdx.y * blockDim.y;
	int index = idy * (blockDim.x * gridDim.x) + idx;

	float times = roundf(log2f(width));

	for(int i = 0; i < times; i++)
	{
		int offsetA = powf(2, i+1);
		int offsetB = powf(2, i);
		//if(index < width-offsetA)
		if(index < width)
		{
			if(index % offsetA == 0)
				data[index + offsetA - 1] += data[index + offsetB - 1];
		}

		__syncthreads();
	}
}

__global__ void DownSweep(float *data, int width)
{
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int idy = threadIdx.y + blockIdx.y * blockDim.y;
	int index = idy * (blockDim.x * gridDim.x) + idx;

	float times = roundf(log2f(width));
    //assert(times == 7);
	//float temp = 0;

	if(index == (width - 1))
		data[index] = 0;

	for(int i = times - 1; i >= 0; i--)
	{
		int offsetA = powf(2, i + 1);
		int offsetB = powf(2, i);

		if(index <= (width - offsetA))
		{
			if(index % offsetA == 0)
			{
				float temp = data[index + offsetB - 1];
				data[index + offsetB - 1] = data[index + offsetA - 1];
				data[index + offsetA - 1] += temp;
			}
		}
		__syncthreads();
	}
}

void scan(float *dataIn, int width)
{
    dim3 threadPerBlock(8, 8);
    dim3 blockPerGrid(1, 2);
    UpSweep<<<blockPerGrid, threadPerBlock>>>(dataIn, SIZE);
    DownSweep<<<blockPerGrid, threadPerBlock>>>(dataIn, SIZE);
}

__global__ void scanShared(float *g_odata, float *g_idata, int n)
{
	 extern __shared__ float temp[]; // allocated on invocation
	 int thid = threadIdx.x;
	 int pout = 0, pin = 1;
	 // Load input into shared memory.
	 // This is exclusive scan, so shift right by one
	 // and set first element to 0
	 temp[pout*n + thid] = (thid > 0) ? g_idata[thid-1] : 0;
	 __syncthreads();
	 for (int offset = 1; offset < n; offset *= 2)
	 {
		   pout = 1 - pout; // swap double buffer indices
		   pin = 1 - pout;
		   if (thid >= offset)
			 temp[pout*n+thid] += temp[pin*n+thid - offset];
		   else
			 temp[pout*n+thid] = temp[pin*n+thid];
		   __syncthreads();
	 }
	 g_odata[thid] = temp[pout*n+thid]; // write output
}


__global__ void scanFirst(float *data, int width)
{
	float times = roundf(log2f(width));

	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int idy = threadIdx.y + blockIdx.y * blockDim.y;
	int index = idy * (blockDim.x * gridDim.x) + idx;

	//assert(times == 7);    // for sure that the time is correct

	for(int i = 0; i < times; i++)
	{
		//int k = 2 << i;  // the powf(2, i)
		int k = powf(2, i);    // k is the stride

		if(index >= k && index < width)
		{
			data[index] = data[index - k] + data[index];
		}
		__syncthreads();
	}
}

/*
 * TODO
__global__ void scanMat(float *dataMat, int row, int col)
{
	int idx = threadIdx.x + blockDim.x * blockIdx.x;
	int idy = threadIdx.y + blockDim.y * blockIdx.y;
	int index = idy * (blockDim.x * gridDim.x) + idx;
}
*/

void print(float *src, int width)
{
	for(int i = 0; i < width; i++)
		cout << src[i] << "  ";
	cout << endl;
}

void scanSeq(float *src, float *dst, int width)
{
	for(int i = 0; i < width; i++)
		dst[i] = dst[i-1] + src[i];
}

int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;
	float *src = new float [SIZE];
	float *dst = new float [SIZE]();
	for(int i = 0; i < SIZE; i++)
		src[i] = i;

	// prepare the cuda event
	cudaEvent_t start, end;
	cudaEventCreate(&start);
	cudaEventCreate(&end);
	float elapsedTime;

	// prepare datas on device
	float *srcD;
	float *dstD;
	cudaError_t cudaState = cudaSuccess;
	cudaState = cudaMalloc((void **)&srcD, SIZE * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(srcD, src, SIZE * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&dstD, SIZE * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemset(dstD, 0, SIZE * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(dstD, srcD, SIZE * sizeof(float), cudaMemcpyDeviceToDevice);

	// sequential version
    cout << "Sequential Versioin : " << endl;
	scanSeq(src, dst, SIZE);

	print(dst, SIZE);

    cout << "Version 1 " << endl;
	cudaEventRecord(start, 0);
	// The first parallel version of scan algorithm
	dim3 threadPerBlock(8, 8);
	dim3 blockPerGrid(1,2);
	scanFirst<<<blockPerGrid, threadPerBlock>>>(dstD, SIZE);

	cudaEventRecord(end, 0);
	cudaEventSynchronize(end);
	cudaEventElapsedTime(&elapsedTime, start, end);

	cudaState = cudaMemcpy(dst, dstD, SIZE * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);
	print(dst, SIZE);

	cout << "Version 1 Parallel Scan: " << elapsedTime << " ms" << endl;

    // Test for complete scan function
    cout << "Version 2: " << endl;
    cudaState = cudaMemcpy(dstD, src, SIZE * sizeof(float), cudaMemcpyHostToDevice);
    assert(cudaState == cudaSuccess);
    cudaEventRecord(start, 0);

    scan(dstD, SIZE);

    cudaEventRecord(end, 0);
    cudaEventSynchronize(end);
    cudaEventElapsedTime(&elapsedTime, start, end);
    cudaState = cudaMemcpy(dst, dstD, SIZE * sizeof(float), cudaMemcpyDeviceToHost);
    assert(cudaState == cudaSuccess);
    cout << "Exclusive Version : " << endl;
    print(dst, SIZE);

    // change the exclusive to inclusive version Scan
    for(int i = 0; i < SIZE - 1; i++)
        dst[i] = dst[i + 1];
    dst[SIZE - 1] += src[SIZE - 1];
    cout << "Inclusive Version : " << endl;
    print(dst, SIZE);

    cout << "Version 2 Parallel Scan: " << elapsedTime << " ms" << endl;

    // Debug for UpSweep and DownSweep Kernels
    /*
	// Test for UpSweep Functioin
	cudaState = cudaMemcpy(dstD, src, SIZE * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	UpSweep<<<blockPerGrid, threadPerBlock>>>(dstD, SIZE);
	cudaState = cudaMemcpy(dst, dstD, SIZE * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);
	print(dst, SIZE);

	// Test for DownSweep Functioni
	DownSweep<<<blockPerGrid, threadPerBlock>>>(dstD, SIZE);
	cudaState = cudaMemcpy(dst, dstD, SIZE * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);
    */

	/*
	// test for the first shared memory version
	//scanShared<<<blockPerGrid, threadPerBlock>>>(dstD, srcD, SIZE);     // Error
	//scanShared<<<1, SIZE>>>(dstD, srcD, SIZE);
	cudaState = cudaMemcpy(dst, dstD, SIZE * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);
	print(dst, SIZE);
	*/

	// free the resources
	delete [] src;
	delete [] dst;

	cudaFree(srcD);
	cudaFree(dstD);

	cudaEventDestroy(start);
	cudaEventDestroy(end);

	return 0;
}
