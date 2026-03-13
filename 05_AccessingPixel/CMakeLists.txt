cmake_minimum_required(VERSION 3.19)
project(5_accessing_pixel)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE( OpenCV REQUIRED )
add_executable(5_accessing_pixel main.cpp)
TARGET_LINK_LIBRARIES( 5_accessing_pixel ${OpenCV_LIBS} )