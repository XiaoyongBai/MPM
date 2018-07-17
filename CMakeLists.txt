cmake_minimum_required(VERSION 2.8)

#project name
PROJECT(MPM)

message(STATUS "This is BINARY dir " ${MPM_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${MPM_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS "-std=c++0x")

#head file path
INCLUDE_DIRECTORIES(
	/usr/local/include
)


#library file path
link_directories(
	/usr/local/lib
	/usr/local/lib/gcc/7/
)


#source directory
add_subdirectory(src)



