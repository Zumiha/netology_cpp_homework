cmake_minimum_required(VERSION 3.5)
project(SearchEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SOURCE_HD SearchEngine.h)
set(SOURCE_LIB SearchEngine.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/libpqxx
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/libpqxx/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/dbmanager
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/serverutils
    "C:/CLibs/boost"
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC 
    IniParser
    UtilsLibs
    pqxx
    DatabaseManager
    ServerUtilsLibs
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)