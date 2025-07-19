cmake_minimum_required(VERSION 3.20.0)
project(UtilsLibs VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "C:/CLibs/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")

# Use file globbing to find libraries
file(GLOB BOOST_SYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_system*.a")
file(GLOB BOOST_FILESYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_filesystem*.a")
file(GLOB BOOST_LOCALE_LIB "${BOOST_ROOT}/stage/lib/libboost_locale*.a")

# Debug: show what was found
message(STATUS "Found system libs: ${BOOST_SYSTEM_LIB}")
message(STATUS "Found filesystem libs: ${BOOST_FILESYSTEM_LIB}")
message(STATUS "Found locale libs: ${BOOST_LOCALE_LIB}")

if(NOT BOOST_SYSTEM_LIB)
    message(FATAL_ERROR "No system library found in ${BOOST_ROOT}/stage/lib")
endif()

if(NOT BOOST_FILESYSTEM_LIB)
    message(FATAL_ERROR "No filesystem library found in ${BOOST_ROOT}/stage/lib")
endif()

if(NOT BOOST_LOCALE_LIB)
    message(FATAL_ERROR "No locale library found in ${BOOST_ROOT}/stage/lib")
endif()

# Find OpenSSL
# find_package(OpenSSL REQUIRED)


set(SOURCE_LIB UrlParser.cpp HTTPUtils.cpp HtmlParser.cpp)
set(SOURCE_HD struct.h UrlParser.h HTTPUtils.h HtmlParser.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_include_directories(${PROJECT_NAME} PRIVATE "${BOOST_ROOT}")
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${BOOST_SYSTEM_LIB}
    ${BOOST_FILESYSTEM_LIB}
    ${BOOST_LOCALE_LIB}
    ssl
    crypto
    ws2_32
    wsock32
)

message(STATUS "Linking with system: ${BOOST_SYSTEM_LIB}")
message(STATUS "Linking with filesystem: ${BOOST_FILESYSTEM_LIB}")
message(STATUS "Linking with locale: ${BOOST_LOCALE_LIB}")
message(STATUS "OpenSSL SSL: ${OPENSSL_SSL_LIBRARY}")
message(STATUS "OpenSSL Crypto: ${OPENSSL_CRYPTO_LIBRARY}")