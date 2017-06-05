#include <iostream>
#include <cassert>
#include <cublas_v2.h>

using namespace std;

// declare constant memory
__constant__ float TestFA[4096];
__constant__ float TestFB[4096];
// declare texture reference
texture<float> texInA;
texture<float> texInB;
//texture<float> texOut;

__global__ void elementDivision(float *A, float *B, float *C)
{
	int x = threadIdx.x + blockDim.x * blockIdx.x;
	int y = threadIdx.y + blockDim.y * blockIdx.y;

	int offset = x + y * blockDim.x * gridDim.x;

	C[offset] = A[offset] / B[offset];
}
__global__ void DivisionConst(float *SUM)
{
	int x = threadIdx.x + blockDim.x * blockIdx.x;
	int y = threadIdx.y + blockDim.y * blockIdx.y;

	int offset = x + y * blockDim.x * gridDim.x;

	SUM[offset] = TestFA[offset] / TestFB[offset];
}
__global__ void DivisionTex(float *SUM)
{
	int x = threadIdx.x + blockDim.x * blockIdx.x;
	int y = threadIdx.y + blockDim.y * blockIdx.y;

	int offset = x + y * blockDim.x * gridDim.x;

	// fetch data from texture
	float a = tex1Dfetch(texInA, offset);
	float b = tex1Dfetch(texInB, offset);

	SUM[offset] =  a / b;
}

int main(void)
{
	cudaError_t cudaState = cudaSuccess;

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	float *TestConstA = new float [4096]();
	float *TestConstB = new float [4096]();
	float *SUM = new float [4096]();

	float *L_d, *R_d, *SUM_d;
	cudaState = cudaMalloc((void **)&L_d, 4096 * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&R_d, 4096 * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&SUM_d, 4096 * sizeof(float));
	assert(cudaState == cudaSuccess);

	for(int i = 0; i < 4096; ++i)
	{
		TestConstA[i] = 2;
		TestConstB[i] = 1;
	}

	dim3 block(16, 16);
	dim3 grid(4096/256);

	float elapsedTime = 0;

	// do division on Constant Memory
	// copy data from host to constant memory
	cudaEventRecord(start, 0);
	cudaState = cudaMemcpyToSymbol(TestFA, TestConstA, 4096 * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpyToSymbol(TestFB, TestConstB, 4096 * sizeof(float));
	assert(cudaState == cudaSuccess);
	// do division on constant memory
	DivisionConst<<<grid, block>>>(SUM_d);
	// copy data from device back to host
	cudaState = cudaMemcpy(SUM, SUM_d, 4096 * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	cout << "Constant Time : " << elapsedTime << " ms" << endl;

	for(int i = 0; i < 4096; ++i)
		if(SUM[i] == 0)
			cout << "There exist errors..." << endl;

	// do division on Global Memory
	// copy data from host to global memory
	cudaEventRecord(start, 0);
	cudaState = cudaMemcpy(L_d, TestConstA, 4096 * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(R_d, TestConstB, 4096 * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	// do division on GPU
	elementDivision<<<grid, block>>>(L_d, R_d, SUM_d);
	// copy data from device back to host
	cudaState = cudaMemcpy(SUM, SUM_d, 4096 * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	cout << "global Time : " << elapsedTime << " ms" << endl;

	for(int i = 0; i < 4096; ++i)
		if(SUM[i] == 0)
			cout << "There exist errors..." << endl;

	cudaEvent_t startT, stopT;
	cudaEventCreate(&startT);
	cudaEventCreate(&stopT);

	// do division on texture meory
	// copy data from host to global memory
	cudaEventRecord(start, 0);
	cudaState = cudaMemcpy(L_d, TestConstA, 4096 * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(R_d, TestConstB, 4096 * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	// bind texture to global memory
	cudaEventRecord(startT, 0);
	cudaState = cudaBindTexture(NULL, texInA, L_d, 4096 * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaBindTexture(NULL, texInB, R_d, 4096 * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaEventRecord(stopT, 0);
	cudaEventSynchronize(stopT);
	cudaEventElapsedTime(&elapsedTime, startT, stopT);
	cout << "Bind texture memory:" << elapsedTime << "ms" << endl;
	// call the kernel
	DivisionTex<<<grid, block>>>(SUM_d);
	// copy result from texture back to hosts
	cudaState = cudaMemcpy(SUM, SUM_d, sizeof(float) * 4096, cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);
	cout << "texture Time : " << elapsedTime << " ms" << endl;

	for(int i = 0; i < 4096; ++i)
		if(SUM[i] == 0)
			cout << "There exist errors..." << endl;


	delete [] TestConstA;
	delete [] TestConstB;
	delete [] SUM;

	// Unbind the texture
	cudaUnbindTexture(texInA);
	cudaUnbindTexture(texInB);

	cudaFree(R_d);
	cudaFree(L_d);
	cudaFree(SUM_d);

	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	return 0;
}
