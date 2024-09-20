cmake_minimum_required(VERSION 3.29)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../cmake/arm-gcc-toolchain.cmake)

project(AnalogDevicesDriver VERSION 0.11 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/no_os/include
    ${CMAKE_SOURCE_DIR}/platform/stm32
)

set(SOURCES
    adin1110.c
    no_os/src/no_os_alloc.c
    no_os/src/no_os_crc8.c
    no_os/src/no_os_list.c
    no_os/src/no_os_mutex.c
    no_os/src/no_os_util.c
    platform/stm32/stm32_delay.c
    platform/stm32/stm32_dma.c
    platform/stm32/stm32_gpio.c
    platform/stm32/stm32_irq.c
    platform/stm32/stm32_spi.c
)

add_library(adin1110 ${SOURCES})
