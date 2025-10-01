cmake_minimum_required(VERSION 3.20.0)
project(DbManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Source files
set(SOURCE_LIB DatabaseManager.cpp DatabasePool.cpp)
set(SOURCE_HD DatabaseManager.h DatabasePool.h)

# Find libpqxx and parser
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../utils)

add_library(DatabaseManager STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_compile_features(DatabaseManager PRIVATE cxx_std_17)
target_link_libraries(DatabaseManager PRIVATE pqxx)
target_link_libraries(DatabaseManager PUBLIC
    IniParser
    UtilsLibs
    SafeThreadPool
    BoostInterface  # Boost interface library from UtilsLibs
)

# Verify Boost path exists
if(EXISTS "C:/CLibs/boost/boost/locale.hpp")
    message(STATUS "Boost locale.hpp found at expected location")
else()
    message(FATAL_ERROR "Boost locale.hpp NOT found at C:/CLibs/boost/boost/locale.hpp")
endif()

target_include_directories(DatabaseManager PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../parser
    ${CMAKE_CURRENT_SOURCE_DIR}/../secqueue
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils
    ${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx/includes
    # ${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx
    "C:/CLibs/boost"
)

target_include_directories(DatabaseManager PRIVATE "C:/CLibs/boost")

set_target_properties(DatabaseManager PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)