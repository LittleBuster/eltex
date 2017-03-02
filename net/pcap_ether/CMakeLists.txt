cmake_minimum_required(VERSION 2.8)
project(sniffer)

include_directories(".")
set(CMAKE_CXX_COMPILER gcc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11 -pedantic -march=native -Wall -O2")
set(SRC_LIST main.c print.c headers.h)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} -lpcap)
