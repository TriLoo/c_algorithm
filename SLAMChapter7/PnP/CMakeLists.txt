cmake_minimum_required(VERSION 3.7)
project(PnP)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INC_DIRS})

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
find_package(G2O REQUIRED)

include_directories(
        ${G2O}_INCLUDE_DIRS
        "/usr/include/eigen3"
)

set(SOURCE_FILES main.cpp)
add_executable(PnP ${SOURCE_FILES})

target_link_libraries(PnP ${OpenCV_LIBS})
target_link_libraries(PnP g2o_core g2o_stuff)

