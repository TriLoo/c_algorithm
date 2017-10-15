cmake_minimum_required(VERSION 3.7)
project(2D2D)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
#message(STATUE ${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(2D2D ${SOURCE_FILES})

target_link_libraries(2D2D ${OpenCV_LIBS})