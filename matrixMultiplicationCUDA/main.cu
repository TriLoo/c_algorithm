#include <iostream>
#include <cassert>
#include <cublas_v2.h>

using namespace std;

__constant__ float SUM_C_d[10 * 10];

int main(void)
{
	cublasHandle_t cublasH;
	cublasStatus_t cublas_status = CUBLAS_STATUS_SUCCESS;
	cudaError_t cudaState = cudaSuccess;

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cublas_status = cublasCreate(&cublasH);
	assert(cublas_status == CUBLAS_STATUS_SUCCESS);

	float *L = new float [512 * 512];
	float *R = new float [512 * 512];
	float *SUM = new float [512 * 512]();
	// initialize the R and L
	for(int i = 0; i < 512 * 512; i++)
	{
		L[i] = 2;
		R[i] = 1;
	}
	int row = 512;
	int rank = 512;
	int col = 512;

	const int SIZEL = 512 * 512;
	const int SIZER = 512 * 512;
	const int SIZES = 512 * 512;
	// malloc memory on Device
	float *L_d, *R_d, *SUM_d;
	cudaState = cudaMalloc((void **)&L_d, SIZEL * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&R_d, SIZER * sizeof(float));
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&SUM_d, SIZES * sizeof(float));
	assert(cudaState == cudaSuccess);

	// copy data from host to device
	cudaState = cudaMemcpy(L_d, L, SIZEL * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(R_d, R, SIZER * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemset(SUM_d, 0, SIZES * sizeof(float));
	assert(cudaState == cudaSuccess);

	float alpha = 1.0, beta = 1.0;

	// Test contant memory
	// copy data from host to constant memory


	// start timing
	cudaEventRecord(start, 0);


	// Call Blas APIs : cublasSgemm()
	cublas_status = cublasSgemm(cublasH, CUBLAS_OP_N, CUBLAS_OP_N, row, col, rank, &alpha, L_d, row, R_d, rank, &beta, SUM_d, row);
	assert(cublas_status == CUBLAS_STATUS_SUCCESS);

	// stop timing
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime = 0;
	cudaEventElapsedTime(&elapsedTime, start, stop);

	cout << "GPU time : " << elapsedTime << " ms" << endl;

	// copy data from device back to host
	cudaState = cudaMemcpy(SUM, SUM_d, SIZES * sizeof(float), cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);

	int count = 0;

	for(int i = 0; i < 512 * 512; ++i)
	{
		if(SUM[i] != 0)
			++count;
		if(i < 10)
			cout << SUM[i] << endl;
	}

	cout << "count = " << count << endl;

	cublas_status = cublasDestroy(cublasH);
	return 0;
}
