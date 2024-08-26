cmake_minimum_required(VERSION 3.18.0)
project(StatLibTest VERSION 0.1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
add_library (GreeterLib STATIC TestLib.cpp TestLib.h)
add_executable(GreeterExe main.cpp)
target_link_libraries(GreeterExe GreeterLib)

#set(CMAKE_SUPPRESS_REGENERATION true)

