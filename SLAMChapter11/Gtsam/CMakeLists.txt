cmake_minimum_required(VERSION 3.7)
project(Gtsam)

set(CMAKE_CXX_STANDARD 11)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# Eigen
include_directories( "/usr/include/eigen3" )

# sophus
find_package( Sophus REQUIRED )
include_directories( ${Sophus_INCLUDE_DIRS} )

# g2o
find_package( G2O REQUIRED )
include_directories( ${G2O_INCLUDE_DIRS} )

find_package( Cholmod REQUIRED )
include_directories( ${CHOLMOD_INCLUDE_DIR} )

# gtsam
find_package( GTSAMCMakeTools )
find_package( GTSAM REQUIRED )
include_directories( ${GTSAM_INCLUDE_DIR} )


# Ceres
find_package( Ceres REQUIRED )
include_directories( ${CERES_INCLUDE_DIRS} )

set(SOURCE_FILES main.cpp)
add_executable(Gtsam ${SOURCE_FILES})
target_link_libraries(Gtsam ${CHOLMOD_LIBRARIES} gtsam)
