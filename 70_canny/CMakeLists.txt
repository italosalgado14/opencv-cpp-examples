cmake_minimum_required(VERSION 3.19)
project(70_canny)

set(CMAKE_CXX_STANDARD 11)
FIND_PACKAGE( OpenCV REQUIRED )
add_executable(70_canny main.cpp edgedetector.h linefinder.h)
TARGET_LINK_LIBRARIES( 70_canny ${OpenCV_LIBS} )