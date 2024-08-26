cmake_minimum_required(VERSION 3.20)
project(BigNumbers VERSION 0.1)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(bignums_source ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs BigInt-build)

add_executable(BigNumbers ${bignums_source})

target_link_libraries(BigNumbers BigInt)
 


