cmake_minimum_required(VERSION 3.20)
project(8_task_03_03 VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(chainresp_source main.cpp chain.h)

add_executable(ChainOfResp ${chainresp_source})
 


