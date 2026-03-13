cmake_minimum_required(VERSION 3.19)
project(06_ReduceColor)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(OpenCV REQUIRED)
add_executable(06_ReduceColor main.cpp)
TARGET_LINK_LIBRARIES(06_ReduceColor ${OpenCV_LIBS} )