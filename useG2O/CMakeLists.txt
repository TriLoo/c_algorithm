cmake_minimum_required(VERSION 3.7)
project(useG2O)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(G2O REQUIRED)
include_directories(
        ${G2O}_INCLUDE_DIRS
        "/usr/include/eigen3"
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(useG2O ${SOURCE_FILES})

target_link_libraries(useG2O ${OpenCV_LIBS} g2o_core g2o_stuff)
