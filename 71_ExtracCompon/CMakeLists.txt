cmake_minimum_required(VERSION 3.19)
project(71_ExtracCompon)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE( OpenCV REQUIRED )
add_executable(71_ExtracCompon main.cpp edgedetector.h linefinder.h)
TARGET_LINK_LIBRARIES( 71_ExtracCompon ${OpenCV_LIBS} )