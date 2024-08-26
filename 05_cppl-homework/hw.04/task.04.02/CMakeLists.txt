cmake_minimum_required(VERSION 3.20.0)
project(TSK0402 VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/src)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(Catch2 Catch2-build)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#set(SOURCE_EXE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set(SOURCE_EXE ${CMAKE_CURRENT_SOURCE_DIR}/test/test-main.cpp)

add_executable(TSK0402 ${SOURCE_EXE})
target_link_libraries(TSK0402 PRIVATE Catch2::Catch2)
target_link_libraries(TSK0402 PUBLIC LLLIB)