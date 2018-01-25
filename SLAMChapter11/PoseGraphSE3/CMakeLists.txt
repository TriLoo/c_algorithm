cmake_minimum_required(VERSION 3.7)
project(PoseGraphSE3)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})
find_package(Cholmod REQUIRED)
#message(${CHOLMOD_INCLUDE_DIR})
include_directories(${CHOLMOD_INCLUDE_DIR})

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")

set(SOURCE_FILES main.cpp)
add_executable(PoseGraphSE3 ${SOURCE_FILES})

target_link_libraries(PoseGraphSE3 g2o_core g2o_stuff g2o_types_slam3d ${CHOLMOD_LIBRARIES} ${Sophus_LIBRARIES})
