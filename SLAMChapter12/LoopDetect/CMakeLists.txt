cmake_minimum_required(VERSION 3.7)
project(LoopDetect)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(DBoW3_INCLUDE_DIRS "/usr/local/include")
set(DBoW3_LIBS "/usr/local/lib/libDBoW3.so")
include_directories(${DBoW3_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(LoopDetect ${SOURCE_FILES})

target_link_libraries(LoopDetect ${OpenCV_LIBS} ${DBoW3_LIBS})

