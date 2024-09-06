cmake_minimum_required(VERSION 3.29)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)

project(BristlemouthNetworkInterface VERSION 0.11 LANGUAGES C)

enable_testing()

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

set(SOURCES
    src/adin2111.c
    # Add more source files as needed
)

add_library(bmnetif ${SOURCES})

target_include_directories(bmnetif PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(test)
