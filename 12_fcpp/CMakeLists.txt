cmake_minimum_required(VERSION 3.5)
project(SearchEngine VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(PROJECT_SOURCES
        main.cpp
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/parser iniparses-build)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/crawler)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PRIVATE IniParser CrawlerDaemon)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/parser
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crawler
)
# include_directories(    ${CMAKE_CURRENT_SOURCE_DIR}/libs/parser
#                         ${CMAKE_CURRENT_SOURCE_DIR}/src/crawler
#                 )
# link_directories(       ${CMAKE_CURRENT_SOURCE_DIR}/libs/parser
#                         ${CMAKE_CURRENT_SOURCE_DIR}/src/crawler
#                 )
