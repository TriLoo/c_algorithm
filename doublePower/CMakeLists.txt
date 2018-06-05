cmake_minimum_required(VERSION 3.7)
project(doublePower)

set(CMAKE_CXX_STANDARD 11)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("std=c++11" COMPILER_SUPPORTS_CXX11)
if (COMPILER_SUPPORTS_CXX11)
    #message(STATUS "Enable")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
endif ()

set(SOURCE_FILES main.cpp)
add_executable(doublePower ${SOURCE_FILES})