cmake_minimum_required(VERSION 3.19)
project(40_histogram)

set(CMAKE_CXX_STANDARD 14)
FIND_PACKAGE( OpenCV REQUIRED )
add_executable(40_histogram main.cpp histogram.h)
TARGET_LINK_LIBRARIES( 40_histogram ${OpenCV_LIBS} )