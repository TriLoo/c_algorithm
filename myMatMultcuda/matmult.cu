#include "matmult.h"

__global__ void matKernel(float *L, float *R, float *C, int m, int k, int n)
{
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;

	//int offset = x + y * blockDim.x * gridDim.x;
	int offset = x + y * n;

	int a = x;    // horizontal
	int b = y;    // vertical

	float sum = 0;

	while(a < n)   // calculate all blocks along the x direction
	{
		while(b < m)    // calculate all blocks along y direction
		{
			sum = 0;
			for(int i = 0; i < k; ++i)
			{
				sum += (L[b * k + i] * R[a + i * n]);
			}
			C[offset] = sum;
			b += blockDim.y * gridDim.y;
			offset = a + b * n;
		}
//		__syncthreads();
		a += blockDim.x * gridDim.x;
		b = y;
		offset = a + b * n;
	}
//	__syncthreads();
}

void matMult::matMultF(matMult *L, matMult *R, matMult *C)
{
	cudaError_t cudaState = cudaSuccess;

	const int SIZEL = L->col * L->row;
	const int SIZER = R->col * R->row;
	const int SIZEC = C->row * C->col;
	// prepare for data, malloc memory on GPU
	cudaState = cudaMalloc((void **)&(L->A_d), SIZEL * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&(R->A_d), SIZER * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&(C->A_d), SIZEC * sizeof(float));
	assert(cudaState == cudaSuccess);

	// copy data from host to device
	cudaState = cudaMemcpy(L->A_d, L->A, SIZEL * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(R->A_d, R->A, SIZER * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemset(C->A_d, 0, SIZEC * sizeof(float));
	assert(cudaState == cudaSuccess);

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// start time record
	cudaEventRecord(start, 0);

	dim3 blockPerGrid(4, 4);
	dim3 threadPerBlock(16, 16);
	//const int Width = blockPerGrid.x * threadPerBlock.x;

	// launch the kernel
	matKernel<<<blockPerGrid, threadPerBlock>>>(L->A_d, R->A_d, C->A_d, L->row, L->col, R->col);

	// stop time record
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime = 0;
	cudaEventElapsedTime(&elapsedTime, start, stop);
	cout << "GPU tiem : " << elapsedTime << " ms" << endl;

	// copy result from device back to host
	cudaState = cudaMemcpy(C->A, C->A_d, SIZEC * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);


	cudaFree(L->A_d);
	cudaFree(R->A_d);
	cudaFree(C->A_d);
}
