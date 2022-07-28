cmake_minimum_required (VERSION 3.10)
project (ray_walk VERSION 1.0 LANGUAGES CXX C)

string(TIMESTAMP PROJECT_DATE_STRING "%b %d, %Y")


include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake")

if ((${CMAKE_SYSTEM_PROCESSOR} STREQUAL "armv7l"))
    set(ON_RASPBERRYPI ON)
endif ()

set(RAY_WALK_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output/bin")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_VERBOSE_MAKEFILE ON)

set(BUILD_TIDY OFF)

if(${BUILD_TIDY})
    set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=^global;
    -checks=-*,readability-*,bugprone-*,performace-*,clang-analyzer-*,modernize-*,hicpp-*;
    )
endif(${BUILD_TIDY})

add_compile_options(
    -Wall
    -O3
    )

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "armv7l")
add_compile_options(
    -mthumb
    -mthumb-interwork
    -march=armv7-a
    )
endif (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "armv7l")

configure_file(${RAY_WALK_CONFIG_DIR}/raywalkconfig.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/raywalkconfig.h)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
#set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/MuonPi/muonpi_db_tool")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "MuonPi <developer@muonpi.org>")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_RESOURCE_FILE_LICENSE "${RAY_WALK_CONFIG_DIR}/license")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output/packages")
set(CPACK_PACKAGE_VENDOR "MuonPi.org")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${PROJECT_VERSION_HASH}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_DEB_COMPONENT_INSTALL ON)

include(CPack)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ray_walk.cmake")
