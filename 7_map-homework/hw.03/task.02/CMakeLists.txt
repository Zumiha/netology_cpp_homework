cmake_minimum_required(VERSION 3.20)
project(07_task_03_02 VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(async_for_each_source main.cpp)

add_executable(asyncforeach ${async_for_each_source})
 


