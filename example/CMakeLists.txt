cmake_minimum_required(VERSION 3.15)

project(variti-slab-examples)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(/usr/include)
include_directories(/usr/include/small/third_party)
include_directories(../include)

add_executable(
  slab-example1
  ../src/util/slab.cpp
  ../src/util/thread_local_slab.cpp
  slab_example1.cpp)
target_link_libraries(
  slab-example1
  small
  pthread)

add_executable(
  slab-example2
  ../src/util/slab.cpp
  ../src/util/thread_local_slab.cpp
  slab_example2.cpp)
target_link_libraries(
  slab-example2
  small
  pthread)

add_executable(
  slab-example3
  ../src/util/slab.cpp
  ../src/util/thread_local_slab.cpp
  slab_example3.cpp)
target_link_libraries(
  slab-example3
  small
  pthread)
