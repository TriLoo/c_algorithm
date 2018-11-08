cmake_minimum_required(VERSION 3.7)
project(testShuffleCUDA)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
#message(STATUS ${CUDA_INCLUDE_DIRS})   # /usr/local/cuda/include
#message(STATUS ${CUDA_LIBRARIES})   # /usr/local/cuda/lib64/...

set(SOURCE_FILES main.cpp testShflCUDA.cu)
# Enable Warp Shuffle function !
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} --gpu-architecture=sm_50)   # -arch is short for --gpu-architecture, determine the comparability of PTX
message(STATUS ${CUDA_NVCC_FLAGS})
#cuda_add_executable(testShflCUDA ${SOURCE_FILES} --sm=5.0)
cuda_add_executable(testShflCUDA ${SOURCE_FILES})

target_link_libraries(testShflCUDA ${OpenCV_LIBS})
target_link_libraries(testShflCUDA ${CUDA_LIBRARIES})
