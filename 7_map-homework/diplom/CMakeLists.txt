cmake_minimum_required(VERSION 3.20)
project(map-diplom VERSION 1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(threadsafequeue_source ${CMAKE_CURRENT_SOURCE_DIR}/src/threadsafequeue.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(threadsafequeue ${threadsafequeue_source})