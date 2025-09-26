cmake_minimum_required(VERSION 3.20.0)
project(SafeThreadPool VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SOURCE_LIB ThreadPool.cpp)
set(SOURCE_HD ThreadPool.h SafeQueue.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})