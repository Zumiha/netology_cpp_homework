cmake_minimum_required(VERSION 3.20.0)
project(IniParser VERSION 1.2)
set(SOURCE_LIB IniParser.cpp)
set(SOURCE_HD IniParser.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

# Export the include directory so other targets can find IniParser.h
# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})