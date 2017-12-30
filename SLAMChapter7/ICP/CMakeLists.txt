cmake_minimum_required(VERSION 3.7)
project(ICP)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INC_DIRS})


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
find_package(G2O REQUIRED)
find_package(CSparse REQUIRED)

include_directories(
        ${G2O}_INCLUDE_DIRS
        ${OpenCV_INCLUDE_DIRS}
        ${CSPARSE_INCLUDE_DIR}
        "/usr/include/eigen3"
)

set(SOURCE_FILES main.cpp)
add_executable(ICP ${SOURCE_FILES})

target_link_libraries(ICP ${OpenCV_LIBS} ${CSPARSE_LIBRARY})
target_link_libraries(ICP g2o_core g2o_stuff g2o_types_sba g2o_csparse_extension)
