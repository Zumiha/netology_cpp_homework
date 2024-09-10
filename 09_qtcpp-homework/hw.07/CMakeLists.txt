cmake_minimum_required(VERSION 3.5)

project(PlotGraphics VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Concurrent)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
    )


qt_add_executable(PlotGraphics
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(PlotGraphics PRIVATE	Qt6::Widgets
                                                Qt6::Charts
                                                Qt6::Concurrent
                                                )
											
qt_finalize_executable(PlotGraphics)
