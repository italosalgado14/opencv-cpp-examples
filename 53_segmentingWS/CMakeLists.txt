cmake_minimum_required(VERSION 3.19)
project(53_segmentingWS)

set(CMAKE_CXX_STANDARD 11)


FIND_PACKAGE( OpenCV REQUIRED )
add_executable(53_segmentingWS main.cpp watershedSegmentation.h)
TARGET_LINK_LIBRARIES( 53_segmentingWS ${OpenCV_LIBS} )