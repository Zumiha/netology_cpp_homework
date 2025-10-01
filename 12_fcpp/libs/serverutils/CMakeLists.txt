cmake_minimum_required(VERSION 3.20.0)
project(ServerUtilsLibs VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../dbmanager)


set(SOURCE_LIB ServerHttpUtils.cpp)
set(SOURCE_HD ServerHttpUtils.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PUBLIC
    UtilsLibs
    pqxx
    DatabaseManager
    BoostInterface  # Boost interface library from UtilsLibs
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils
    ${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx
    ${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dbmanager
    "C:/CLibs/boost"
)

target_include_directories(${PROJECT_NAME} PRIVATE "C:/CLibs/boost")