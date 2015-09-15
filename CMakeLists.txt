# ------------------------------------------------------------------------
#
#                               CMake Lists.txt for cdlList
#                                        V 0.01
#
#                             (c) Brian Lynch September, 2015
#
# ------------------------------------------------------------------------
cmake_minimum_required (VERSION 2.8)
project(cdlList)

#Set the location of the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

#Use c++11
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

#Set the executable .cpp source dependencies
set(src cdlList_Test.cpp)

#Add the executable, which will be in build/bin
add_executable(cdlList_Test ${src})
