cmake_minimum_required(VERSION 3.20.0)
project(UtilsLibs VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "C:/CLibs/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")

set(BOOST_BOOSTDIR "${BOOST_ROOT}/boost")
set(BOOST_LOCALEDIR "C:/CLibs/boost/boost/locale")



# Use file globbing to find libraries
file(GLOB BOOST_SYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_system*.dll.a")
file(GLOB BOOST_FILESYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_filesystem*.dll.a")
file(GLOB BOOST_LOCALE_LIB "${BOOST_ROOT}/stage/lib/libboost_locale*.dll.a")


set(SOURCE_LIB UrlParser.cpp HTTPUtils.cpp HtmlParser.cpp Indexer.cpp)
set(SOURCE_HD struct.h UrlParser.h HTTPUtils.h HtmlParser.h Indexer.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_include_directories(${PROJECT_NAME} PUBLIC  "${BOOST_ROOT}" 
                                                    "${BOOST_INCLUDEDIR}" 
                                                    "${BOOST_LIBRARYDIR}"
                                                    "${BOOST_BOOSTDIR}"
                                                    "${BOOST_LOCALEDIR}"
                                                    )


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