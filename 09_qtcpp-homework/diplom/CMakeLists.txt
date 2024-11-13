cmake_minimum_required(VERSION 3.5)

project(AirportMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Sql Concurrent)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.h mainwindow.cpp
        mainwindow.ui
        dbdata.h dbdata.cpp
        dbdata.ui
        database.h database.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/parser)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/parser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/parser iniparses-build)

add_executable(AirportMonitor ${PROJECT_SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(AirportMonitor PRIVATE Qt6::Widgets
                                            Qt6::Gui
                                            Qt6::Sql
                                            Qt6::Concurrent
                                            IniParser)
