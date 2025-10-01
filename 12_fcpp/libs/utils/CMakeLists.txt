cmake_minimum_required(VERSION 3.20.0)
project(UtilsLibs VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(BOOST_ROOT "C:/CLibs/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")


#Check if headers exist
if (NOT EXISTS "${BOOST_ROOT}/boost/locale.hpp")
	message(FATAL_ERROR "Boost headers not found at ${BOOST_ROOT}/boost/")
endif()

# Use file globbing to find libraries
file(GLOB BOOST_SYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_system*.dll")
file(GLOB BOOST_FILESYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_filesystem*.dll")
file(GLOB BOOST_LOCALE_LIB "${BOOST_ROOT}/stage/lib/libboost_locale*.dll")
file(GLOB BOOST_BEAST_LIB "${BOOST_ROOT}/stage/lib/libboost_beast*.dll")

# file(GLOB BOOST_SYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_system*.a")
# file(GLOB BOOST_FILESYSTEM_LIB "${BOOST_ROOT}/stage/lib/libboost_filesystem*.a")
# file(GLOB BOOST_LOCALE_LIB "${BOOST_ROOT}/stage/lib/libboost_locale*.a")

if (NOT BOOST_SYSTEM_LIB OR NOT BOOST_FILESYSTEM_LIB OR NOT BOOST_LOCALE_LIB)
	message (FATAL_ERROR "One of more Boost libraries not found in ${BOOST_LIBRARYDIR}")
endif()

# Create Boost interface library for shared configuration
add_library(BoostInterface INTERFACE)
target_include_directories(BoostInterface INTERFACE 
    "${BOOST_ROOT}"
    "${BOOST_ROOT}/boost"  # Add Beast include
)

target_link_libraries(BoostInterface INTERFACE 
    ${BOOST_SYSTEM_LIB}
    ${BOOST_FILESYSTEM_LIB}
    ${BOOST_LOCALE_LIB}
    ${BOOST_BEAST_LIB}
)

set(SOURCE_LIB UrlParser.cpp HTTPUtils.cpp HtmlParser.cpp Indexer.cpp)
set(SOURCE_HD struct.h UrlParser.h HTTPUtils.h HtmlParser.h Indexer.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIB} ${SOURCE_HD})

# Then modify UtilsLibs to use it:
target_link_libraries(${PROJECT_NAME} PUBLIC BoostInterface)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ssl
    crypto
    ws2_32
    wsock32
)