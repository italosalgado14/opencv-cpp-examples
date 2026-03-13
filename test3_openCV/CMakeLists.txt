cmake_minimum_required(VERSION 3.19)
project(test3_openCV)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE( OpenCV REQUIRED )
add_executable(test3_openCV main.cpp)
TARGET_LINK_LIBRARIES( test3_openCV ${OpenCV_LIBS} )