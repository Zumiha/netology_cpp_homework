cmake_minimum_required(VERSION 3.20.0)
project(UtilsLibs VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "C:/CLibs/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")
set(BOOST_INCLUDE "${BOOST_ROOT}/include")

# set(Boost_USE_STATIC_LIBS ON)
# find_package (Boost COMPONENTS system filesystem locale)

include_directories(${BOOST_INCLUDEDIR})
include_directories(${BOOST_LIBRARYDIR})
include_directories(${BOOST_INCLUDE})
include_directories(${Boost_INCLUDE_DIRS})

# Use file globbing to find libraries
file(GLOB BOOST_SYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_system*.dll")
file(GLOB BOOST_FILESYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_filesystem*.dll")
file(GLOB BOOST_LOCALE_LIB "${BOOST_ROOT}/stage/lib/libboost_locale*.dll")

# file(GLOB BOOST_SYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_system*.a")
# file(GLOB BOOST_FILESYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_filesystem*.a")
# file(GLOB BOOST_LOCALE_LIB "${BOOST_ROOT}/stage/lib/libboost_locale*.a")


set(SOURCE_LIB UrlParser.cpp HTTPUtils.cpp HtmlParser.cpp Indexer.cpp)
set(SOURCE_HD struct.h UrlParser.h HTTPUtils.h HtmlParser.h Indexer.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

target_include_directories(${PROJECT_NAME} PUBLIC  "${BOOST_ROOT}" 
                                                    "${BOOST_INCLUDEDIR}" 
                                                    "${BOOST_LIBRARYDIR}"
                                                    "${BOOST_INCLUDE}"
                                                    )

# target_include_directories(${PROJECT_NAME} PRIVATE  "${BOOST_ROOT}" 
#                                                     "${BOOST_INCLUDEDIR}" 
#                                                     "${BOOST_LIBRARYDIR}"
#                                                     "${BOOST_INCLUDE}"
#                                                     )
													


target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${BOOST_SYSTEM_LIB}
    ${BOOST_FILESYSTEM_LIB}
    ${BOOST_LOCALE_LIB}
	${Boost_LIBRARIES}
	# Boost::system
	# Boost::filesystem
	# Boost::locale
    ssl
    crypto
    ws2_32
    wsock32
)

# message(STATUS "Linking with system: ${BOOST_SYSTEM_LIB}")
# message(STATUS "Linking with filesystem: ${BOOST_FILESYSTEM_LIB}")
# message(STATUS "Linking with locale: ${BOOST_LOCALE_LIB}")
# message(STATUS "OpenSSL SSL: ${OPENSSL_SSL_LIBRARY}")
# message(STATUS "OpenSSL Crypto: ${OPENSSL_CRYPTO_LIBRARY}")