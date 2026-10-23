cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(rp2350_rainbow C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(rainbow
    main.c
)

pico_generate_pio_header(rainbow ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
target_link_libraries(rainbow pico_stdlib hardware_pio hardware_clocks)
pico_enable_stdio_usb(rainbow 1)
pico_enable_stdio_uart(rainbow 0)
pico_add_extra_outputs(rainbow)
