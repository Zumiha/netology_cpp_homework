cmake_minimum_required(VERSION 3.20.0)
project(dbx VERSION 1.0)
set(SOURCE_LIB dbx.cpp)
set(SOURCE_HD dbx.h)

set(SKIP_BUILD_TEST ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx-7.9.0 libpq-build) # путь к libpq++

add_library(dbx SHARED ${SOURCE_LIB} ${SOURCE_HD})
target_compile_features(dbx PRIVATE cxx_std_17) # включить C++17
target_link_libraries(dbx pqxx)
