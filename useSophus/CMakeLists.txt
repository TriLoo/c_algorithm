cmake_minimum_required(VERSION 3.7)
project(Chapter4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

#include(/home/smher/myCode/SLAMs/Chapter4/Sophus/cmake_modules/FindEigen3.cmake)

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

add_executable(Chapter4 ${SOURCE_FILES})
target_link_libraries(Chapter4 ${Sophus_LIBRARIES})
