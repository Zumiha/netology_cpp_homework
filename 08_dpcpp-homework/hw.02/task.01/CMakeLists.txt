cmake_minimum_required(VERSION 3.20)
project(8_task_02_01 VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(textdecor main.cpp textdecor.h)

add_executable(DecoratinText ${textdecor})
 


