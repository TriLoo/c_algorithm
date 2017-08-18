#include "GFilter.h"
#include <cassert>
#include <cuda.h>
#include <cuda_runtime.h>

// declare texture memory reference
texture<float, cudaTextureType2D, cudaReadModeElementType> texA, texB;

__constant__ float d_eps;

// declare constant memory

#define BLOCK_SIZE 32
// TODO : change this macro define to kernel parameter to decide the size of shared memory in boxfilter_kernel
#define BOXWIDTH 17
// R : row, C : col, N : colNums
#define INDX(R, C, N) ((R) * (N) + (C))

/*
#define FILTER 0
#define FILTER_WIDTH 5
#define FILTER_RAD (FILTER_WIDTH / 2)

#define BLOCKSIZE 32
#define INNER_TILE_WIDTH (BLOCKSIZE - FILTER_RAD * 2)

#define INDX(row, col, wid) (((row) * (wid)) + (col))

__global__ void boxfilter_kernel(const float * const inputChannel, float *const outputChannel, int wid, int hei, const float * __restrict__ const filter)
{
    // shared memory data (+1 to avoid bank conflict
    __shared__ float sh_matrix[BLOCKSIZE+1][BLOCKSIZE];

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int bx = blockIdx.x;
    int by = blockIdx.y;

    int tileX = bx * INNER_TILE_WIDTH + tx;   // cols
    int tileY = by * INNER_TILE_WIDTH + ty;   // rows

    // if tileX_image < 0, then it must be outside of the image
    int tileX_image = tileX - FILTER_RAD;
    int tileY_image = tileY - FILTER_RAD;

    // fill shared memory
    if((tileX_image >= 0) && (tileX_image < wid) && (tileY_image >= 0) && (tileY_image < hei))
        sh_matrix[ty][tx] = inputChannel[INDX(tileY_image, tileX_image, wid)];
    else
        sh_matrix[ty][tx] = 0;

    __syncthreads();

    // Do convolution (only in the inner tile of block)
    float res = 0.0f;
    if(tx < INNER_TILE_WIDTH && ty < INNER_TILE_WIDTH)
    {
        for(int fr = 0; fr < FILTER_WIDTH; ++fr)
            for(int fc = 0; fc < FILTER_WIDTH; ++fc)
                res += sh_matrix[fr + ty][fc + tx] * filter[INDX(fr, fc, FILTER_WIDTH)];

        if(tileX < wid && tileY < hei)
            outputChannel[INDX(tileY_image, tileX_image, wid)] = res;
    }
}
*/
// calculate the variance of varI based on texture memory
// out : corrIp and convIp,
__global__ void variance_kernel(float *out, float *lhs, int wid, int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    if(idx >= wid || idy >= hei)
        return ;

    float val = 0.f;

    val = tex2D(texA, idy, idx);
    val *= val;

    val = lhs[INDX(idy, idx, wid)] - val;

    out[INDX(idy, idx, wid)] = val;
}

__global__ void covariance_kernel(float *out, float *lhs, int wid, int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    if(idx >= wid || idy >= hei)
        return ;

    float val = 0.0f;

    val = tex2D(texA, idy, idx);
    val *= tex2D(texB, idy, idx);

    out[INDX(idy, idx, wid)] = lhs[INDX(idy, idx, wid)] - val;
}

// input 3 variables : meanP, meanI and "a", the former two are stored in texture now
__global__ void calcuB_kernel(float *out, float *in, int wid, int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    if(idx >= wid || idy >= hei)
        return ;

    float val;
    val = in[INDX(idy, idx, wid)];

    val *= tex2D(texA, idy, idx);

    val = tex2D(texB, idy, idx) - val;

    out[INDX(idy, idx, wid)] = val;
}

__device__ int clamp(int a, int b, int c)
{
    int temp = a > b ? a : b;
    return (temp < c ? temp : c);
}

// boxfilter based on share memory
__global__ void boxfilter_kernel(float * const d_in, float * const d_out, int wid, int hei, const float * __restrict__ filter, const int filterWidth)
{
    const unsigned int x0 = threadIdx.x;
    const unsigned int y0 = threadIdx.y;

    const int tx = x0 + blockIdx.x * blockDim.x;
    const int ty = y0 + blockIdx.y * blockDim.y;

    if(tx >= wid || ty >= hei)
        return ;

    const int filterRadius = filterWidth / 2;
    float value = 0.f;

    __shared__ float shMat[BLOCK_SIZE + BOXWIDTH - 1][BLOCK_SIZE + BOXWIDTH - 1];

    int fx, fy;
    // case 1 : upper left
    fx = tx - filterRadius;    // col
    fy = ty - filterRadius;    // row
    fx = clamp(fx, 0, wid);
    fy = clamp(fy, 0, hei);
    shMat[x0][y0] = d_in[INDX(fy, fx, wid)];

    // case 2 : upper right
    fx = tx + filterRadius;
    fy = ty - filterRadius;
    fx = clamp(fx, 0, wid);
    fy = clamp(fy, 0, hei);
    shMat[x0 + filterWidth - 1][y0] = d_in[INDX(fy, fx, wid)];

    // case 3 : lower left
    fx = tx - filterRadius;
    fy = ty + filterRadius;
    fx = clamp(fx, 0, wid);
    fy = clamp(fy, 0, hei);
    shMat[x0][y0 + filterWidth - 1] = d_in[INDX(fy, fx, wid)];

    // case 4 : lower right
    fx = fx + filterRadius;
    fy = fy + filterRadius;
    fx = clamp(fx, 0, wid);
    fy = clamp(fy, 0, hei);
    shMat[x0+filterWidth - 1][y0 + filterWidth - 1] = d_in[INDX(fy, fx, wid)];

    __syncthreads();

    for(int i = 0; i < filterWidth; ++i)
        for (int j = 0; j < filterWidth; ++j)
        {
            value += filter[INDX(j, i, filterWidth)] * shMat[x0+i][y0+j];
        }
    d_out[INDX(ty, tx, wid)] = value;
}

// calculate the image I based on texture memory
__global__ void boxfilterTI_kernel(float *out, int wid, int hei, const size_t pitch, const int fWid, const int fHei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    float outputVal = 0.0f;

    if(idx < wid && idy < hei)
    {
        for(int i = -fWid; i <= fWid; ++i)
        {
            for(int j = -fHei; j <= fHei; ++j)
                outputVal += tex2D(texA, idy + j, idx + i);
        }
        outputVal /= ((2 * fWid + 1) * (2 * fHei + 1));

        int offset = idy * pitch / sizeof(float) + idx;
        out[offset] = outputVal;
    }
}
__global__ void boxfilterTP_kernel(float *out, int wid, int hei, const size_t pitch, const int fWid, const int fHei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    float outputVal = 0.0f;

    if(idx < wid && idy < hei)
    {
        for(int i = -fWid; i <= fWid; ++i)
        {
            for(int j = -fHei; j <= fHei; ++j)
                outputVal += tex2D(texB, idy + j, idx + i);
        }
        outputVal /= ((2 * fWid + 1) * (2 * fHei + 1));

        int offset = idy * pitch / sizeof(float) + idx;
        out[offset] = outputVal;
    }
}

__global__ void elemwisemult_kernel(float *out, size_t pitch, const int wid, const int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    int offset = idy * pitch / sizeof(float) + idx;

    float res = 0.f;

    if(idx < wid && idy < hei)
    {
        res = tex2D(texA, idy, idx) * tex2D(texB, idy, idx);
    }

    out[offset] = res;
}

/*
__global__ void elemwisemult_kernel(float *out, float *inA, float *inB, size_t pitch, const int wid, const int hei)
{
    extern __shared__ float A[];
    extern __shared__ float B[];

    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;
    //int index = idy * blockDim.x * gridDim.x + idx;
    int offset = idy * pitch / sizeof(float) + idx;

    int sharedIdx = threadIdx.y * blockDim.x + threadIdx.x;

    if(idx < wid && idy < hei)
    {
        A[sharedIdx] = inA[offset];
        B[sharedIdx] = inB[offset];
        //A[threadIdx.x][threadIdx.y] = inA[index];
        //B[threadIdx.x][threadIdx.y] = inB[index];

        __syncthreads();

        out[offset] = A[sharedIdx] * B[sharedIdx];
    }
}
*/

__global__ void elemwisemultSame_kernel(float *out, const size_t pitch, const int wid, const int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    float outputVal = 0.0f;

    if(idx < wid && idy < hei)
    {
        outputVal = tex2D(texA, idy, idx);
        outputVal *= outputVal;
    }

    int offset = idy * pitch / sizeof(float) + idx;
    out[offset] = outputVal;
}

/*
// dir means the operation : 0 for add, 1 for subtraction
__global__ void elewiseAdd_kernel(float *lhs, float *rhs, int dir, int wid, int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    int index = idy * wid + idx;

    if(idx < wid && idy < hei)
    {
        if(dir == 0)   // for operation +
            lhs[index] += rhs[index];
        else if(dir == 1)    // for operation -
            lhs[index] -= rhs[index];
        else
            lhs[index] = lhs[index];
    }
}
*/

// the img I is binded to texA, so the source operators are in1, in2 only
// in1 : meanA, in2 : meanB
__global__ void finnalCal_kernel(float * const out, const float * const in1, const float * const in2, int wid, int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    if(idx >= wid || idy >= hei)
        return ;

    float val = 0.f;

    val = in1[INDX(idy, idx, wid)] * tex2D(texA, idy, idx);

    val += in2[INDX(idy, idx, wid)];

    out[INDX(idy, idx, wid)] = val;
}

__global__ void elewiseDiv_kernel(float *lhs, float *rhs, int wid, int hei)
{
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    int idy = threadIdx.y + blockDim.y * blockIdx.y;

    //int index = idy * wid + idx;

    if(idx < wid && idy < hei)
    {
        lhs[INDX(idy, idx, wid)] /= rhs[INDX(idy, idx, wid)] + d_eps;
    }
}

// allocate page-locked memory on host cudaHostAlloc, use cudaFreeHost to free them
void GFilter::prepareMem(float *dataInI, float *dataInP)
{

}

void GFilter::createfilter()
{
    //const int filterSize = (2 * rad + 1) * (2 * rad + 1);
    filter = new float [FILTERSIZE];
    for(int i = 0; i < FILTERSIZE; ++i)
        filter[i] = 1.0 / FILTERSIZE;
}

/*
void GFilter::boxfilter(float *d_in, float *d_out, int rad, const float * const __restrict__ filter)
{
    dim3 threadPerBlock(BLOCKSIZE, BLOCKSIZE);
    dim3 blockPerGrid((width + threadPerBlock.x - 1) / BLOCKSIZE, (height + threadPerBlock.y - 1) / BLOCKSIZE);
}
*/

void GFilter::guidedfilter()
{
    // copy data from host to device
    // allocate pitch memory on device use cudaMallocPitch
    size_t pitch = 0;
    cudaError_t cudaState = cudaSuccess;
    cudaState = cudaMallocPitch((void **)&d_imgI, &pitch, width, height);   // pitch' unit is bytes !
    assert(cudaState == cudaSuccess);
    cudaState = cudaMallocPitch((void **)&d_imgP, &pitch, width, height);
    assert(cudaState == cudaSuccess);
    // allocate temp data on device use cudaMalloc
    cudaState = cudaMalloc((void **)&d_meanI, sizeof(float) * width * height);
    assert(cudaState == cudaSuccess);
    cudaState = cudaMalloc((void **)&d_meanP, sizeof(float) * width * height);
    assert(cudaState == cudaSuccess);
    cudaState = cudaMalloc((void **)&d_tempA, sizeof(float) * width * height);
    assert(cudaState == cudaSuccess);
    cudaState = cudaMalloc((void **)&d_tempB, sizeof(float) * width * height);
    assert(cudaState == cudaSuccess);
    // copy data from host to device use cudaMemcpy2D
    // the dst pitch and src pitch all are in bytes
    cudaState = cudaMemcpy2D(d_imgI, pitch, h_imgI, sizeof(float) * width, sizeof(float) * width, height, cudaMemcpyHostToDevice);
    assert(cudaState == cudaSuccess);
    cudaState = cudaMemcpy2D(d_imgP, pitch, h_imgP, sizeof(float) * width, sizeof(float) * width, height, cudaMemcpyHostToDevice);
    assert(cudaState == cudaSuccess);

    // prepare the texture memory
    cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
    texA.addressMode[0] = texA.addressMode[1] = cudaAddressModeBorder;
    // bind the 2D Pitch memory to 2D texture memory
    cudaState = cudaBindTexture2D(NULL, texA, d_imgI, channelDesc, width, height, pitch);
    assert(cudaState == cudaSuccess);
    cudaState = cudaBindTexture2D(NULL, texB, d_imgP, channelDesc, width, height, pitch);
    assert(cudaState == cudaSuccess);

    /*
    // prepare the filter on device constant memory by using cudaMemcpyToSymbol
    createfilter();
    cudaState = cudaMemcpyToSymbol(d_);
    */
    createfilter();
    cudaState = cudaMalloc((void **)&d_filter, FILTERSIZE * sizeof(float));
    assert(cudaState == cudaSuccess);
    cudaState = cudaMemcpy(d_filter, filter, FILTERSIZE * sizeof(float), cudaMemcpyHostToDevice);
    assert(cudaState == cudaSuccess);


    // prepare the kernel launching parameters
    dim3 threadPerBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 blockPerGrid;
    blockPerGrid.x = (width + threadPerBlock.x - 1) / threadPerBlock.x;
    blockPerGrid.y = (height + threadPerBlock.y - 1) / threadPerBlock.y;

    // launch boxfilter kernel with stream technology
    cudaStream_t st[4];
    // create stream use cudaStreamCreate
    for(int i = 0; i < 4; ++i)
    {
        cudaState = cudaStreamCreate(&st[i]);
        assert(cudaState == cudaSuccess);
    }

    boxfilterTI_kernel<<<blockPerGrid, threadPerBlock, 0, st[0]>>>(d_meanI, width, height, pitch, rad, rad);
    boxfilterTP_kernel<<<blockPerGrid, threadPerBlock, 0, st[1]>>>(d_meanP, width, height, pitch, rad, rad);
    elemwisemultSame_kernel<<<blockPerGrid, threadPerBlock, 0, st[2]>>>(d_tempA, pitch, width, height);
    elemwisemult_kernel<<<blockPerGrid, threadPerBlock, 0, st[3]>>>(d_tempB, pitch, width, height);

    // synchronize all above  streams use cudaDeviceSyncthronize()
    cudaState = cudaDeviceSynchronize();
    assert(cudaState == cudaSuccess);

    // calculate the corrI and corrIp
    boxfilter_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempA, d_tempA, width, height, d_filter, FILTERWIDTH);
    boxfilter_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempB, d_tempB, width, height, d_filter, FILTERWIDTH);

    // change the texA to d_meanI
    // Unbind the texA from origin d_imgI
    cudaState = cudaUnbindTexture(texA);
    assert(cudaState == cudaSuccess);
    // rebind the texA to d_meanI
    // the pitch of d_meanI is width * sizeof(float)
    cudaState = cudaBindTexture2D(NULL, texA, d_meanI, channelDesc, width, height, width * sizeof(float));
    assert(cudaState == cudaSuccess);

    // calculation the variance of I: varI
    variance_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempA, d_tempA, width, height);

    // rebind the texB to d_meanP
    // unbind the texB from d_imgP;
    cudaState = cudaUnbindTexture(texB);
    assert(cudaState == cudaSuccess);
    // bind the texB to d_meanp
    cudaState = cudaBindTexture2D(NULL, texB, d_meanP, channelDesc, width, height, sizeof(float) * width);
    assert(cudaState == cudaSuccess);
    // calculate the covariance of I and P based on global memory
    covariance_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempB, d_tempB, width, height);

    // calculate the a & b
    // calculate the "a" and store it in d_tempB
    // copy eps to device constant memory which is d_eps
    cudaState = cudaMemcpyToSymbol(d_eps, &eps, sizeof(float), NULL, cudaMemcpyDefault);
    assert(cudaState == cudaSuccess);
    // launch the kernel function
    elewiseDiv_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempB, d_tempA, width, height);

    /*
    // rebind texB to above "a"
    cudaState = cudaUnbindTexture(texB);
    assert(cudaState == cudaSuccess);
    // bind the texB to "a" which is in d_tempB
    cudaState = cudaBindTexture2D(NULL, texB, d_tempB, channelDesc, sizeof(float) * width);
    assert(cudaState == cudaSuccess);
    */

    // calculate the "b" and store it in tempA
    // launch the the kernel function
    calcuB_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempA, d_tempB, width, height);


    // calculate the boxfilter of "a"  &  "b"
    // calculate meanA based on d_tempB
    boxfilter_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempB, d_tempB, width, height, d_filter, FILTERWIDTH);
    // calculate meaB based on d_tempA
    boxfilter_kernel<<<blockPerGrid, threadPerBlock>>>(d_tempA, d_tempA, width, height, d_filter, FILTERWIDTH);

    // calculate the finnal output: guided filtering result
    Res = new float [width * height];
    // rebind the texA to d_imgI
    // unbind the texA from d_meanI
    cudaState = cudaUnbindTexture(texA);
    assert(cudaState == cudaSuccess);
    // rebind the texA to d_imgI
    cudaState = cudaBindTexture2D(NULL, texA, d_imgI, width, height, pitch);
    assert(cudaState == cudaSuccess);
    finnalCal_kernel<<<blockPerGrid, threadPerBlock>>>(d_meanI, d_tempB, d_tempA, width, height);

    // Finnal step : copy data from device back to host
    cudaState = cudaMemcpy(Res, d_meanI, sizeof(float) * width * height, cudaMemcpyHostToDevice);
    assert(cudaState == cudaSuccess);


    // Unbind all textures
    cudaState = cudaUnbindTexture(texB);
    assert(cudaState == cudaSuccess);
    cudaState = cudaUnbindTexture(texA);
    assert(cudaState == cudaSuccess);


    // destory streams use cudaStreamDestory
    for(int i = 0; i < 4; i++)
    {
        cudaState = cudaStreamDestroy(st[i]);
        assert(cudaState == cudaSuccess);
    }

    if(d_imgI)
        cudaFree(d_imgI);
    if(d_imgP)
        cudaFree(d_imgP);
    if(d_tempA)
        cudaFree(d_tempA);
    if(d_tempB)
        cudaFree(d_tempB);
    if(d_meanI)
        cudaFree(d_meanI);
    if(d_meanP)
        cudaFree(d_meanP);
    if(d_filter)
        cudaFree(d_filter);

}

GFilter::~GFilter()
{
    /*
    if(d_imgI)
        cudaFree(d_imgI);
    if(d_imgP)
        cudaFree(d_imgP);
    if(d_tempA)
        cudaFree(d_tempA);
    if(d_tempB)
        cudaFree(d_tempB);
    if(d_meanI)
        cudaFree(d_meanI);
    if(d_meanP)
        cudaFree(d_meanP);
    if(d_filter)
        cudaFree(d_filter);

    if(filter)
        delete [] filter;

    if(Res)
        delete [] Res;
    */
}
