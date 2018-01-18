cmake_minimum_required(VERSION 3.7)
project(chapter10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS  "-O2")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(OpenCV REQUIRED)
#message(STATUS ${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}) #Error: OpenCV_INC_DIRS

find_package(G2O REQUIRED)
find_package(Eigen3 REQUIRED)
message(STATUS ${G2O_INCLUDE_DIRS})
include_directories(${G2O_INCLUDE_DIRS})
include_directories(${CSPARSE_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")
set(G2O_LIBS g2o_core g2o_types_sba g2o_solver_csparse g2o_stuff g2o_csparse_extension)

set(SOURCE_FILES main.cpp)
add_executable(chapter10 ${SOURCE_FILES})

#message(STATUS ${G2O_LIBS})
target_link_libraries(chapter10 ${OpenCV_LIBS} ${G2O_LIBS})