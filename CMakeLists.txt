# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(HW3)
# Set the output folder where your program will be created
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
find_package(OpenCV REQUIRED)
add_executable(HW3 HW3F.cpp)
target_link_libraries(HW3 ${OpenCV_LIBS})
# The following folder will be included
#include_directories("${PROJECT_SOURCE_DIR}")
