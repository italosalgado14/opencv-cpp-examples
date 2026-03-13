cmake_minimum_required(VERSION 3.19)
project(121_BGFG)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE( OpenCV REQUIRED )
add_executable(121_BGFG main.cpp BGFGSegmentor.h videoprocessor.h)
TARGET_LINK_LIBRARIES( 121_BGFG ${OpenCV_LIBS} )