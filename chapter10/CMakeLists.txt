cmake_minimum_required(VERSION 3.7)
project(chapter10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS  "-O2")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(OpenCV REQUIRED)
#message(STATUS ${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}) #Error: OpenCV_INC_DIRS

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(G2O REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Cholmod REQUIRED)
#message(STATUS ${CSPARSE_INCLUDE_DIRS})
include_directories(${G2O_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR} ${CHOLMOD_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/ceres)
include_directories(${PROJECT_SOURCE_DIR}/common
            ${PROJECT_SOURCE_DIR}/common/tools
            ${PROJECT_SOURCE_DIR}/common/flags
        )
#include_directories(${CSPARSE_INCLUDE_DIR})

include_directories("/usr/include/eigen3")
set(G2O_LIBS g2o_cli g2o_ext_freeglut_minimal g2o_simulator g2o_solver_slam2d_linear
        g2o_types_icp g2o_types_slam2d g2o_types_sba g2o_types_slam3d g2o_core g2o_interface
        g2o_solver_csparse g2o_solver_structure_only g2o_csparse_extension g2o_opengl_helper g2o_solver_dense
        g2o_stuff g2o_types_sclam2d g2o_parser g2o_solver_pcg g2o_types_data g2o_types_sim3 cxsparse )

#message(STATUS ${G2O_LIBS})
add_library(BALProblem SHARED ${PROJECT_SOURCE_DIR}/common/BALProblem.cpp)
add_library(ParseCmd SHARED ${PROJECT_SOURCE_DIR}/common/flags/command_args.cpp)

set(SOURCE_FILES main.cpp)
add_executable(chapter10 ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${G2O_LIBS} ${CHOLMOD_LIBRARIES} BALProblem ParseCmd)
