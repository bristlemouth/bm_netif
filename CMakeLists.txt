cmake_minimum_required(VERSION 3.29)

if(NOT ENABLE_TESTING)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)
endif()

project(BristlemouthNetworkInterface VERSION 0.11 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

add_compile_definitions(ADIN2111)
add_compile_definitions(SPI_OA_EN)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/stm32u5
)

set(SOURCES
    src/bm_adin2111.c
    src/adin2111.c
    src/adi_phy.c
    src/adi_mac.c
    src/adi_spi_oa.c
    # src/stm32u5/hal.c
)

add_library(bmnetif ${SOURCES})

target_include_directories(bmnetif PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

if(ENABLE_TESTING)
    set(CMAKE_CXX_FLAGS "-g -Wall -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "-g -Wall -W -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

    enable_testing()
    add_subdirectory(test)
endif()
