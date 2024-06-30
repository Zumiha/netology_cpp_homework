cmake_minimum_required(VERSION 3.20)
project(8_task_03_01 VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(logcmd_source main.cpp logcommand.h)

add_executable(LogCommand ${logcmd_source})
 


