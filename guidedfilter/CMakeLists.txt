cmake_minimum_required(VERSION 2.8)
project(GFilter)
message(STATUS "Project Name : GFilter")
message(STATUS "Project Dir  : ${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 11)

include(/usr/share/cmake-2.8/Modules/FindCUDA.cmake)
include_directories(./)

set(SOURCE_FILES main.cu GFilter.cu)
cuda_add_executable(GFilter ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)

link_directories(/usr/local/cuda/lib64)
link_libraries(/usr/local/cuda/lib64)
set(CUDA_DIR /usr/local/cuda/lib64)

target_link_libraries(GFilter ${OpenCV_LIBS})
target_link_libraries(GFilter ${CUDA_DIR}/libcublas.so)
