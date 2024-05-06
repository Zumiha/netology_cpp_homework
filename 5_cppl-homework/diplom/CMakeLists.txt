cmake_minimum_required(VERSION 3.20)
project(Parser VERSION 0.1)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(source_file ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib iniparses-build)

add_executable(${PROJECT_NAME} ${source_file})
target_link_libraries(${PROJECT_NAME} IniParser)