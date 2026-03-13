cmake_minimum_required(VERSION 3.19)
project(44_countingPixels2)

set(CMAKE_CXX_STANDARD 11)


add_executable(44_countingPixels2 main.cpp integral.h histogram.h)

FIND_PACKAGE( OpenCV REQUIRED )
project(44_countingPixels2)
TARGET_LINK_LIBRARIES( 44_countingPixels2 ${OpenCV_LIBS} )






