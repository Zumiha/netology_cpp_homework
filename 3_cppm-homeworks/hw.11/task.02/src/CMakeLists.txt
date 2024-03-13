cmake_minimum_required(VERSION 3.18.0)
project(DynLibTest VERSION 0.1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library (LeaverLib SHARED TestDynLib.cpp TestDynLib.h)
add_executable(LeaverExe main.cpp)
target_link_libraries(LeaverExe LeaverLib)

#set(CMAKE_SUPPRESS_REGENERATION true)

