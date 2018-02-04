cmake_minimum_required(VERSION 3.7)
project(PointCloudMap)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")

find_package(PCL REQUIRED COMPONENT common io filters)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

#find_package(Boost REQUIRED COMPONENT system format)

set(SOURCE_FILES main.cpp)
add_executable(PointCloudMap ${SOURCE_FILES})

target_link_libraries(PointCloudMap ${OpenCV_LIBS} ${PCL_LIBRARIES})
