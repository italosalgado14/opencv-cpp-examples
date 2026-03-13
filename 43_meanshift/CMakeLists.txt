cmake_minimum_required(VERSION 3.19)
project(43_meanshift)

set(CMAKE_CXX_STANDARD 11)
FIND_PACKAGE( OpenCV REQUIRED )
add_executable(43_meanshift main.cpp colorhistogram.h contentFinder.h)
TARGET_LINK_LIBRARIES( 43_meanshift ${OpenCV_LIBS} )