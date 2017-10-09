cmake_minimum_required(VERSION 3.7)
project(chapter5)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

# add opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# add eigen
include_directories(/usr/include/eigen3)

#add pcl
find_package(PCL REQUIRED COMPONENT common io)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(SOURCE_FILES main.cpp)
add_executable(chapter5 ${SOURCE_FILES})

target_link_libraries(chapter5 ${OpenCV_LIBS} ${PCL_LIBRARIES})