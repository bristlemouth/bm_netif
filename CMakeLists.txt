cmake_minimum_required(VERSION 3.25)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Test")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)
endif()

project(BristlemouthNetworkInterface VERSION 0.11 LANGUAGES C)

enable_testing()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

set(SOURCES
    src/bm_adin2111.c
    # Add more source files as needed
)

add_library(bmnetif ${SOURCES})

target_include_directories(bmnetif PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

if(CMAKE_BUILD_TYPE STREQUAL "Test")
    add_subdirectory(test)
endif()
