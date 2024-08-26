cmake_minimum_required(VERSION 3.20)
project(07_task_01_01 VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(queuethreads_source main.cpp)

add_executable(queuethreads ${queuethreads_source})
 


