cmake_minimum_required(VERSION 3.19)
project(4_ROI)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE( OpenCV REQUIRED )
add_executable(4_ROI main.cpp)
TARGET_LINK_LIBRARIES( 4_ROI ${OpenCV_LIBS} )