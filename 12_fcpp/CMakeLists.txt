cmake_minimum_required(VERSION 3.5)
project(SearchAndCrawl VERSION 0.5 LANGUAGES CXX)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Find libpqxx and libpq
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(PQXX REQUIRED libpqxx)
# pkg_check_modules(PQ REQUIRED libpq)

# Alternative method
# find_path(PQXX_INCLUDE_DIR pqxx/pqxx)
# find_library(PQXX_LIBRARY pqxx)
# find_library(PQ_LIBRARY pq)

set(PROJECT_SOURCES
        main.cpp
)

# shared libraries subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/parser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/secqueue)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/libpqxx)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/dbmanager)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/serverutils)

# project subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/crawler)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/searchengine)

add_executable(WebCrawler 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crawler/Crawler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crawler/Crawler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crawler/main_crawl.cpp
)

add_executable(WebSearch
       ${CMAKE_CURRENT_SOURCE_DIR}/src/searchengine/SearchEngine.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/searchengine/SearchEngine.h
       ${CMAKE_CURRENT_SOURCE_DIR}/src/searchengine/main_search.cpp
)

set_property(TARGET WebCrawler PROPERTY CXX_STANDARD 20)
set_property(TARGET WebSearch PROPERTY CXX_STANDARD 20)

target_link_libraries(WebCrawler PRIVATE CrawlerDaemon)
# target_link_libraries(WebSearch PUBLIC UtilsLibs)
target_link_libraries(WebSearch PRIVATE SearchEngine)


target_include_directories(WebCrawler PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crawler
)

target_include_directories(WebSearch PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/searchengine
)