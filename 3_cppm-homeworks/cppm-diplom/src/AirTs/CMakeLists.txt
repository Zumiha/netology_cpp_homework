cmake_minimum_required(VERSION 3.18.0)
project(ATLib VERSION 1.0)
set(SOURCE_DLL vehicle.h vehicle.cpp AirTs.h AirTs.cpp eagle.h eagle.cpp carpet.h carpet.cpp broom.h broom.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_DLL})