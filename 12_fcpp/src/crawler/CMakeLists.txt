cmake_minimum_required(VERSION 3.5)
project(CrawlerDaemon VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_HD Crawler.h)
set(SOURCE_LIB Crawler.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

# Link to IniParser since Crawler.cpp uses it
target_link_libraries(${PROJECT_NAME} PUBLIC IniParser)

# Include IniParser headers
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/parser
)