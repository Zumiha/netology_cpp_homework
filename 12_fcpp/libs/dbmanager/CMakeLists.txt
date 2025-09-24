cmake_minimum_required(VERSION 3.20.0)
project(DbManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Source files
set(SOURCE_LIB DatabaseManager.cpp DatabasePool.cpp)
set(SOURCE_HD DatabaseManager.h DatabasePool.h)

# Find libpqxx
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx)
# if(NOT TARGET pqxx)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libpqxx libpqxx-build)
# endif()

add_library(DatabaseManager STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_compile_features(DatabaseManager PRIVATE cxx_std_17)
target_link_libraries(DatabaseManager PRIVATE pqxx)
target_link_libraries(DatabaseManager PUBLIC
    UtilsLibs
    SafeThreadPool
)


target_include_directories(DatabaseManager PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/secqueue
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/libpqxx
)

set_target_properties(DatabaseManager PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)