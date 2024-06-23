cmake_minimum_required(VERSION 3.20)
project(8_task_01_03 VERSION 2.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(query_builder main.cpp sql_query_builder.h)

add_executable(SqlSelectQueryBuilder ${query_builder})
 


