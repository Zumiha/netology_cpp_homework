cmake_minimum_required(VERSION 3.20.0)
project(SafeThreadPool VERSION 1.0)

set(SOURCE_LIB ThreadPool.cpp)
set(SOURCE_HD ThreadPool.h SafeQueue.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})