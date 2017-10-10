cmake_minimum_required(VERSION 3.7)
project(useCeres)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 11)

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )
#include(/home/smher/myCode/SLAMs/chapter6/useCeres/cmake_modules/CeresConfig.cmake.in)

find_package( Ceres REQUIRED )
include_directories(${CERES_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(useCeres ${SOURCE_FILES})

target_link_libraries(useCeres ${OpenCV_LIBS} ${CERES_LIBRARIES})

