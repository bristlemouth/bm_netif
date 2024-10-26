cmake_minimum_required(VERSION 3.29)

if(NOT ENABLE_TESTING)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)
endif()

project(BristlemouthNetworkInterface VERSION 0.11 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

include(FetchContent)
FetchContent_Declare(
  bm_common
  GIT_REPOSITORY https://github.com/bristlemouth/bm_common.git
  GIT_TAG        feat/aligned-malloc
)
FetchContent_MakeAvailable(bm_common)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/stm32u5
    ${bm_common_SOURCE_DIR}/include
)

set(SOURCES
    src/adi_fcs.c
    src/adi_mac.c
    src/adi_phy.c
    src/adi_spi_oa.c
    src/adin2111.c
    src/bm_adin2111.c
)

add_library(bmnetif ${SOURCES})

target_include_directories(bmnetif PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

if(ENABLE_TESTING)
    set(CMAKE_CXX_FLAGS "-g -Wall --coverage")
    set(CMAKE_C_FLAGS "-g -Wall -W --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "--coverage")
    add_compile_definitions(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
