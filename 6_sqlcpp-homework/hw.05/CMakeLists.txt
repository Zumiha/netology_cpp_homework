cmake_minimum_required(VERSION 3.20)
project(DBeditor VERSION 1.1)

#set(SKIP_BUILD_TEST ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(dbeditor_source ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)






include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs ${CMAKE_CURRENT_SOURCE_DIR}/libs/dbx ${CMAKE_CURRENT_SOURCE_DIR}/src)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/libpqxx-7.9.0 libpq-build) # путь к libpq++
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/dbx dbx-build)

add_executable(dbeditor ${dbeditor_source})
target_compile_features(dbeditor PRIVATE cxx_std_17) # включить C++17

target_link_libraries(dbeditor dbx)
#target_link_libraries(dbeditor pqxx)
 


