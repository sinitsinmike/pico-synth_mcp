cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(pico_synth C CXX ASM)

pico_sdk_init()

# ---- Sources ---------------------------------------------------------
file(GLOB_RECURSE SOURCE_C
    "*.c"
    "tui/*.c"
    "midi/*.c"
)
# Exclude feature sources (built as a separate lib)
list(FILTER SOURCE_C EXCLUDE REGEX "/features/")

add_executable(pico-synth ${SOURCE_C})

# Generate PIO header(s) if present
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/driver-mcp4822.pio")
  pico_generate_pio_header(pico-synth ${CMAKE_CURRENT_LIST_DIR}/driver-mcp4822.pio)
endif()

target_include_directories(pico-synth PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/tui/include
    ${CMAKE_CURRENT_LIST_DIR}/midi/include
)

add_subdirectory(features)

target_link_libraries(pico-synth
    pico_synth_features

    pico_stdlib
    pico_multicore

    hardware_pio
    hardware_dma
    hardware_gpio
    hardware_i2c
    hardware_uart
    hardware_timer
    hardware_clocks
    hardware_pll
    hardware_vreg
    hardware_xosc

    pico_unique_id
)

pico_enable_stdio_uart(pico-synth 1)
pico_enable_stdio_usb(pico-synth 0)

pico_add_extra_outputs(pico-synth)
