cmake_minimum_required(VERSION 3.7)
project(DenseMapSingle)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(DenseMapSingle ${SOURCE_FILES})

target_link_libraries(DenseMapSingle ${Sophus_LIBRARIES} ${OpenCV_LIBS})
