cmake_minimum_required(VERSION 3.19)
project(32_representingHSB)

set(CMAKE_CXX_STANDARD 11)
FIND_PACKAGE( OpenCV REQUIRED )
add_executable(32_representingHSB main.cpp)
TARGET_LINK_LIBRARIES( 32_representingHSB ${OpenCV_LIBS} )