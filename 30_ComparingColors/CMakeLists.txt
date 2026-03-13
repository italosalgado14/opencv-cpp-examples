cmake_minimum_required(VERSION 3.19)
project(30_ComparingColors)

set(CMAKE_CXX_STANDARD 11)
FIND_PACKAGE( OpenCV REQUIRED )
add_executable(30_ComparingColors main.cpp colordetector.h colordetector.cpp)
TARGET_LINK_LIBRARIES(30_ComparingColors ${OpenCV_LIBS} )