cmake_minimum_required(VERSION 3.20.0)
project(UtilsLibs VERSION 1.0)

set(SOURCE_LIB UrlParser.cpp)
set(SOURCE_HD UrlParser.h )
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})