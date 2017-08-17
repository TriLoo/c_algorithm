/* ***
 * This file realize the box filter based on shared memory but not texture memory
 */

#include <iostream>
#include <cassert>

using namespace std;

#define INDX(row, col, colNum) (((row) * (colNum)) + col)

#define SIZE 100

#define BLOCKSIZE 16

#define FILTER_WIDTH 3
#define FILTER_RAD (FILTER_WIDTH / 2)
#define INNER_TILE (BLOCKSIZE - FILTER_RAD)

__global__ void boxfilter_kernel(float *dataIn, float *dataOut, int wid, int hei, const float * const __restrict__ filter)
{
	__shared__ float shMat[BLOCKSIZE][BLOCKSIZE];

	int tx = threadIdx.x;
	int ty = threadIdx.y;

	int idx = tx + blockIdx.x * blockDim.x;
	int idy = ty + blockIdx.y * blockDim.y;

	int offset = idx + idy * blockDim.x * gridDim.x;

	if(tx < wid && ty < hei)
		shMat[ty][tx] = dataIn[offset];
	else
		shMat[ty][tx] = 0;

	/*
	// load data to shared memory
	if((tileX >= 0) && (tileX < wid) && (tileY >= 0) && (tileY < hei))
		shMat[ty][tx] = dataIn[INDX(tileY, tileX, wid)];
	else
		shMat[ty][tx] = 0;
	 */
	__syncthreads();

	float res = 0.0f;

	if((tx > FILTER_RAD) && (tx < INNER_TILE) && (ty > FILTER_RAD) && (ty < INNER_TILE))
	{
		for(int fr = -FILTER_RAD; fr < FILTER_RAD; ++fr)
		{
			for(int fc = -FILTER_RAD; fc < FILTER_RAD; ++fc)
			{
				res += shMat[fr + ty][fc + tx] * filter[INDX(fr, fc, FILTER_WIDTH)];
			}
		}

		if(idx < wid && idy < hei)
			dataOut[INDX(idy, idx, wid)] = res;
	}
}

int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	float *img = new float [SIZE];

	for(int i = 0; i < SIZE; ++i)
		img[i] = 1;

	float *filter = new float [FILTER_WIDTH * FILTER_WIDTH];
	for(int i = 0; i < FILTER_WIDTH; ++i)
		for(int j = 0; j < FILTER_WIDTH; ++j)
		{
			filter[INDX(i, j, FILTER_WIDTH)] = 1 / (FILTER_WIDTH * FILTER_WIDTH);
		}



	int width = 10;
	int height = 10;

	float *d_in, *d_out;
	cudaError_t cudaState = cudaSuccess;
	cudaState = cudaMalloc((void **)&d_in, sizeof(float) * width * height);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&d_out, sizeof(float) * width * height);
	assert(cudaState == cudaSuccess);

	// copy data from host to device
	cudaState = cudaMemcpy(d_in, img, sizeof(float) * SIZE, cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	float *d_filter ;
	cudaState = cudaMalloc((void **)&d_filter, FILTER_WIDTH * FILTER_WIDTH * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(d_filter, filter, FILTER_WIDTH * FILTER_WIDTH * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);

	dim3 threadPerBlock(BLOCKSIZE, BLOCKSIZE);
	dim3 blockPerGrid;
	blockPerGrid.x = (width + threadPerBlock.x - 1) / BLOCKSIZE;
	blockPerGrid.y = (height + BLOCKSIZE - 1) / BLOCKSIZE;

	boxfilter_kernel<<<blockPerGrid, threadPerBlock>>>(d_in, d_out, width, height, d_filter);

	// copy data back to host
	cudaState = cudaMemcpy(img, d_out, sizeof(float) * SIZE, cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);

	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; ++j)
			cout << img[INDX(i, j, 10)] << "; ";
		cout << endl;
	}

	delete [] img;

	return 0;
}
