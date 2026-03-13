cmake_minimum_required(VERSION 3.19)
project(test4_openCV)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE( OpenCV REQUIRED )
add_executable(test4_openCV main.cpp)
TARGET_LINK_LIBRARIES( test4_openCV ${OpenCV_LIBS} )