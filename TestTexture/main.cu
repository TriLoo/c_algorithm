/* ************
 *  This file is attempted to test the relation ship between the bounded device memory and bounding texture memory.
 *  Result :
 *  When the values in device memory changed, the texture memory should change as well, as long as the BOUNDING relationship is working.
 *	When you bind linear memory to texture, u should use tex1Dfetch to fetch the contents in texture memory.
 * 	tex1D API is used only to one-dimension array
 */



#include <iostream>
#include <cassert>

using namespace std;

#define SIZE 10

texture<float, cudaTextureType1D, cudaReadModeElementType> texIn;

__global__ void testTex(float *Out)
{
	int idx = threadIdx.x;

	if(idx < SIZE)
		Out[idx] = tex1Dfetch(texIn, idx);
}

void printMat(float *data)
{
	for(int i = 0; i < SIZE; i++)
		cout << data[i] << "; ";
	cout << endl;
}

int main(void)
{
	float *data = new float [SIZE];
	float *out = new float [SIZE];

	// first version
	for(int i = 0; i < SIZE; i++)
		data[i] = i;

	cout << "Input : " << endl;
	printMat(data);

	cudaError_t cudaState = cudaSuccess;

	// malloc global memory on GPU
	float *d_data, *d_out;
	cudaState = cudaMalloc((void **)&d_data, sizeof(float) * SIZE);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMemcpy(d_data, data, sizeof(float) * SIZE, cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);
	cudaState = cudaMalloc((void **)&d_out, sizeof(float) * SIZE);
	assert(cudaState == cudaSuccess);

	// create texture memory
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
	texIn.addressMode[0] = cudaAddressModeWrap;
	cudaState = cudaBindTexture(NULL, texIn, d_data, channelDesc, SIZE * sizeof(float));
	assert(cudaState == cudaSuccess);

	// launch kernel function
	testTex<<<1, SIZE>>>(d_out);

	// copy data back to host
	cudaState = cudaMemcpy(out, d_out, sizeof(float) * SIZE, cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);

	// print the result
	printMat(out);

	/*
	// change the input data
	cudaState = cudaMemset(d_data, 0, SIZE * sizeof(float));   // Caution : every byte is set to 1, the unit is BYTE !
	assert(cudaState == cudaSuccess);
*/

	for(int i = 0; i < SIZE; i++)
		data[i] = 2 * i;

	cudaState = cudaMemcpy(d_data, data, SIZE * sizeof(float), cudaMemcpyHostToDevice);
	assert(cudaState == cudaSuccess);

	testTex<<<1, SIZE>>>(d_out);

	// copy data back to host
	cudaState = cudaMemcpy(out, d_out, sizeof(float) * SIZE, cudaMemcpyDeviceToHost);
	assert(cudaState == cudaSuccess);

	// print the result
	printMat(out);


	cudaUnbindTexture(texIn);

	delete [] data;
	delete [] out;

	return 0;
}
