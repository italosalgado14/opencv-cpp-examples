cmake_minimum_required(VERSION 3.19)
project(41_histogramColor)

set(CMAKE_CXX_STANDARD 11)
FIND_PACKAGE( OpenCV REQUIRED )
add_executable(41_histogramColor main.cpp histogram.h colorhistogram.h contentFinder.h)
TARGET_LINK_LIBRARIES( 41_histogramColor ${OpenCV_LIBS} )