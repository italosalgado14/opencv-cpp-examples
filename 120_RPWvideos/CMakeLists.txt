cmake_minimum_required(VERSION 3.19)
project(120_RPWvideos)

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE( OpenCV REQUIRED )
add_executable(120_RPWvideos main.cpp videoprocessor.h)
TARGET_LINK_LIBRARIES( 120_RPWvideos ${OpenCV_LIBS} )