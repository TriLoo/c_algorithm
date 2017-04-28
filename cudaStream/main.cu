#include <iostream>

#define N (256 * 256)
#define FULL_DATA_SIZE (N*20)

using namespace std;

__global__ void kernel(int *a, int *b, int *c)
{
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	if(idx < N)
	{
		int idx1 = (idx + 1) % 256;
		int idx2 = (idx + 2) % 256;
		float as = (a[idx] + a[idx1] + a[idx2]) / 3.0f;
		float bs = (b[idx] + b[idx1] + b[idx2]) / 3.0f;
		c[idx] = (as + bs) / 2;
	}
}

int main(int argc, char **argv)
{
	cudaDeviceProp prop;
	int whichDevice;
	cudaGetDevice(&whichDevice);
	cout << "which Device = " << whichDevice << endl;
	cudaGetDeviceProperties(&prop, whichDevice);
	if(!prop.deviceOverlap)
	{
		cout << "Device will not handle overlaps" << endl;
		return 0;
	}

	// create cuda event to calculate the time
	cudaEvent_t start, stop;
	float elapsedTime;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	// initialize the streams
	cudaStream_t stream0, stream1;
	cudaStreamCreate(&stream0);
	cudaStreamCreate(&stream1);

	// malloc data
	int *host_a, *host_b, *host_c;
	int *dev_a0, *dev_b0, *dev_c0;
	int *dev_a1, *dev_b1, *dev_c1;

	cudaMalloc((void **)&dev_a0, N * sizeof(int));
	cudaMalloc((void **)&dev_b0, N * sizeof(int));
	cudaMalloc((void **)&dev_c0, N * sizeof(int));
	cudaMalloc((void **)&dev_a1, N * sizeof(int));
	cudaMalloc((void **)&dev_b1, N * sizeof(int));
	cudaMalloc((void **)&dev_c1, N * sizeof(int));

	// allocate page-locked memory , used to stream
	cudaHostAlloc((void **)&host_a, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void **)&host_b, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void **)&host_c, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);

	for(int i = 0; i < FULL_DATA_SIZE; i++)
	{
		host_a[i] = rand();
		host_b[i] = rand();
	}

	for(int i = 0; i < FULL_DATA_SIZE; i+=N*2)
	{
		cudaMemcpyAsync(dev_a1,host_a+i + N, N*sizeof(int), cudaMemcpyHostToDevice, stream1);
		cudaMemcpyAsync(dev_b1,host_b+i + N, N*sizeof(int), cudaMemcpyHostToDevice, stream1);
		cudaMemcpyAsync(dev_a0,host_a+i, N*sizeof(int), cudaMemcpyHostToDevice, stream0);
		cudaMemcpyAsync(dev_b0,host_b+i, N*sizeof(int), cudaMemcpyHostToDevice, stream0);

		kernel<<<N/256, 256, 0, stream1>>>(dev_a1, dev_b1, dev_c1);
		kernel<<<N/256, 256, 0, stream0>>>(dev_a0, dev_b0, dev_c0);

		cudaMemcpyAsync(host_c+i + N, dev_c1, N*sizeof(int), cudaMemcpyDeviceToHost, stream1);
		cudaMemcpyAsync(host_c+i, dev_c0, N*sizeof(int), cudaMemcpyDeviceToHost, stream0);
	}

	cudaStreamSynchronize(stream0);
	cudaStreamSynchronize(stream1);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);

	cout << "total time : " << elapsedTime << " ms" << endl;

	cudaFreeHost(host_a);
	cudaFreeHost(host_b);
	cudaFreeHost(host_c);
	cudaFree(dev_a0);
	cudaFree(dev_b0);
	cudaFree(dev_c0);
	cudaFree(dev_a1);
	cudaFree(dev_b1);
	cudaFree(dev_c1);

	// destroy stream
	cudaStreamDestroy(stream0);
	cudaStreamDestroy(stream1);

	return 0;
}

/*  **** with no gpu scheduling **** */
/*
int main(int argc, char **argv)
{
	cudaDeviceProp prop;
	int whichDevice;
	cudaGetDevice(&whichDevice);
	cout << "which Device = " << whichDevice << endl;
	cudaGetDeviceProperties(&prop, whichDevice);
	if(!prop.deviceOverlap)
	{
		cout << "Device will not handle overlaps" << endl;
		return 0;
	}

	// create cuda event to calculate the time
	cudaEvent_t start, stop;
	float elapsedTime;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	// initialize the streams
	cudaStream_t stream0, stream1;
	cudaStreamCreate(&stream0);
	cudaStreamCreate(&stream1);

	// malloc data
	int *host_a, *host_b, *host_c;
	int *dev_a0, *dev_b0, *dev_c0;
	int *dev_a1, *dev_b1, *dev_c1;

	cudaMalloc((void **)&dev_a0, N * sizeof(int));
	cudaMalloc((void **)&dev_b0, N * sizeof(int));
	cudaMalloc((void **)&dev_c0, N * sizeof(int));
	cudaMalloc((void **)&dev_a1, N * sizeof(int));
	cudaMalloc((void **)&dev_b1, N * sizeof(int));
	cudaMalloc((void **)&dev_c1, N * sizeof(int));

	// allocate page-locked memory , used to stream
	cudaHostAlloc((void **)&host_a, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void **)&host_b, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void **)&host_c, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);

	for(int i = 0; i < FULL_DATA_SIZE; i++)
	{
		host_a[i] = rand();
		host_b[i] = rand();
	}

	for(int i = 0; i < FULL_DATA_SIZE; i+=N*2)
	{
		cudaMemcpyAsync(dev_a0,host_a+i, N*sizeof(int), cudaMemcpyHostToDevice, stream0);
		cudaMemcpyAsync(dev_b0,host_b+i, N*sizeof(int), cudaMemcpyHostToDevice, stream0);

		kernel<<<N/256, 256, 0, stream0>>>(dev_a0, dev_b0, dev_c0);

		cudaMemcpyAsync(host_c+i, dev_c0, N*sizeof(int), cudaMemcpyDeviceToHost, stream0);

		cudaMemcpyAsync(dev_a1,host_a+i + N, N*sizeof(int), cudaMemcpyHostToDevice, stream1);
		cudaMemcpyAsync(dev_b1,host_b+i + N, N*sizeof(int), cudaMemcpyHostToDevice, stream1);

		kernel<<<N/256, 256, 0, stream1>>>(dev_a1, dev_b1, dev_c1);

		cudaMemcpyAsync(host_c+i + N, dev_c1, N*sizeof(int), cudaMemcpyDeviceToHost, stream1);
	}

	cudaStreamSynchronize(stream0);
	cudaStreamSynchronize(stream1);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start, stop);

	cout << "total time : " << elapsedTime << " ms" << endl;

	cudaFreeHost(host_a);
	cudaFreeHost(host_b);
	cudaFreeHost(host_c);
	cudaFree(dev_a0);
	cudaFree(dev_b0);
	cudaFree(dev_c0);
	cudaFree(dev_a1);
	cudaFree(dev_b1);
	cudaFree(dev_c1);

	// destroy stream
	cudaStreamDestroy(stream0);
	cudaStreamDestroy(stream1);



	return 0;
}
*/

/* ******* only one stream ********* */
/*
int main(int argc, char **argv)
{
	cudaDeviceProp prop;
	int whichDevice;
	cudaGetDevice(&whichDevice);
	cout << "which Device = " << whichDevice << endl;
	cudaGetDeviceProperties(&prop, whichDevice);
	if(!prop.deviceOverlap)
	{
		cout << "Device will not handle overlaps" << endl;
		return 0;
	}

	// create cuda event to calculate the time
	cudaEvent_t start, stop;
	float elapsedTime;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	// initialize the stream
	cudaStream_t stream;
	cudaStreamCreate(&stream);

	// malloc data
	int *host_a, *host_b, *host_c;
	int *dev_a, *dev_b, *dev_c;

	cudaMalloc((void **)&dev_a, N * sizeof(int));
	cudaMalloc((void **)&dev_b, N * sizeof(int));
	cudaMalloc((void **)&dev_c, N * sizeof(int));

	// allocate page-locked memory , used to stream
	cudaHostAlloc((void **)&host_a, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void **)&host_b, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);
	cudaHostAlloc((void **)&host_c, FULL_DATA_SIZE * sizeof(int), cudaHostAllocDefault);

	for(int i = 0; i < FULL_DATA_SIZE; i++)
	{
		host_a[i] = rand();
		host_b[i] = rand();
	}

	// loop over full data, in bite-size chunks
	for(int i = 0; i < FULL_DATA_SIZE; i += N)
	{
		cudaMemcpyAsync(dev_a, host_a+i,N*sizeof(int), cudaMemcpyHostToDevice, stream);
		cudaMemcpyAsync(dev_b, host_b+i,N*sizeof(int), cudaMemcpyHostToDevice, stream);
		cudaMemcpyAsync(dev_c, host_c+i,N*sizeof(int), cudaMemcpyHostToDevice, stream);

		kernel<<<N/256, 256, 0, stream>>>(dev_a, dev_b, dev_c);

		cudaMemcpyAsync(host_c+i, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost, stream);
	}


	cudaStreamSynchronize(stream);

	cudaEventRecord(stop, 0);

	cudaEventSynchronize(stop);

	cudaEventElapsedTime(&elapsedTime, start, stop);

	cout << "total time : " << elapsedTime << " ms" << endl;

	cudaFreeHost(host_a);
	cudaFreeHost(host_b);
	cudaFreeHost(host_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	// destroy stream
	cudaStreamDestroy(stream);


	return 0;
}
*/
