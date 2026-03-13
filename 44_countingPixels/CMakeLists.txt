cmake_minimum_required(VERSION 3.19)
project(44_countingPixels)

set(CMAKE_CXX_STANDARD 11)

add_executable(44_countingPixels main.cpp integral.h)

FIND_PACKAGE( OpenCV REQUIRED )
cmake_minimum_required(VERSION 3.19)
project(44_countingPixels)
TARGET_LINK_LIBRARIES( 44_countingPixels ${OpenCV_LIBS} )

