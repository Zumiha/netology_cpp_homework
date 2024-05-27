cmake_minimum_required(VERSION 3.20)
project(07_task_02_02 VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(progressbar_source main.cpp)

add_executable(progressbar ${progressbar_source})
 


