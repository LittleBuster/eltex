cmake_minimum_required(VERSION 2.8)
project(udpmake)

include_directories(".")
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11 -pedantic -march=native -Wall -O2")
set(SRC_LIST main.c headers.h)
set(SRC_LIST2 listener.c)

add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(server ${SRC_LIST2})
