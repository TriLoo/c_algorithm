cmake_minimum_required(VERSION 3.7)
project(LK)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INC_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(LK ${SOURCE_FILES})

target_link_libraries(LK ${OpenCV_LIBS})
