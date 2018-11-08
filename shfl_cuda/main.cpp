/**
 * @author smh
 * @date 2018.11.06
 *
 * @brief 测试CUDA里面的shufl指令。
 *
 * shfl
 *      1. instruction to exchange data in a warp
 *      2. threads can 'read' other threads' register
 *      3. no shared memory is needed
 *      4. it is available starting from SM3.0
 */
#include <iostream>
// see:  https://stackoverflow.com/questions/6302695/difference-between-cuda-h-cuda-runtime-h-cuda-runtime-api-h
// nvcc can take care of inclusion of all the required headers automatically without programmer intervention.
#include <cuda.h>               // defines the public host functions and types for the CUDA runtime API
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>       // defines everything cuda_runtime_api.h does, as well as built-in type definitions and function overlays for the CUDA language extensions and device intrinsic functions.

#include "testShflCUDA.h"

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;


int main() {
    Mat img = imread("lena.jpg", IMREAD_COLOR);
    imshow("input", img);
    cvWaitKey();

    testShfl temp;
    temp.testShflKernel();

    int tempSum = 0.0;
    for(int i = 0; i < 32; ++i)
        tempSum += i;
    cout << "warp reduction on CPU: " << tempSum << endl;


    return 0;
}
