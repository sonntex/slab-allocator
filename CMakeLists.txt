cmake_minimum_required(VERSION 3.15)

project(variti-slab)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(/usr/include)
include_directories(/usr/include/small/third_party)
include_directories(include)

add_library(
  variti-slab
  src/util/slab.cpp
  src/util/thread_local_slab.cpp)
