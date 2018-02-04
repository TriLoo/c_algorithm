cmake_minimum_required(VERSION 3.7)
project(OctoMap)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")

find_package(PCL REQUIRED COMPONENT common io filters)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

#find_package(octomap REQUIRED)
#include_directories("/opt/ros/indigo/include/")
find_package(octomap REQUIRED)
include_directories(${OCTOMAP_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
#set(SOURCE_FILES octomap_mapping.cpp)
add_executable(OctoMap ${SOURCE_FILES})

target_link_libraries(OctoMap ${OCTOMAP_LIBRARIES})
target_link_libraries(OctoMap ${OpenCV_LIBS} ${PCL_LIBRARIES})
