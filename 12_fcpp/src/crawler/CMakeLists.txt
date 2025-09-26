cmake_minimum_required(VERSION 3.5)
project(CrawlerDaemon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SOURCE_HD Crawler.h)
set(SOURCE_LIB Crawler.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/dbmanager DatabaseManager-build)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_link_libraries(${PROJECT_NAME} PUBLIC 
    IniParser 
    UtilsLibs
	SafeThreadPool
    pqxx
    DatabaseManager
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/secqueue
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/libpqxx
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/dbmanager
)