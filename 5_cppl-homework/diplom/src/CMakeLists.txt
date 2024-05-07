cmake_minimum_required(VERSION 3.20)
project(Parser VERSION 1.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(source_file ${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_SOURCE_DIR}/../src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib iniparses-build)

add_executable(${PROJECT_NAME} ${source_file})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} IniParser)
