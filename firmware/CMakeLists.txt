# SPDX-License-Identifier: BSD-3-Clause
# Drop-in replacement CMakeLists.txt for firmware/
# - Uses keyword-style target_link_libraries (PRIVATE) everywhere
# - Adds features subdir and screen-features sources
# - Ensures UF2 output via pico_add_extra_outputs
# - Globs *.c in firmware/ (not recursive) to include main/synth/screen/midi-impl files

cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-synth C CXX ASM)

pico_sdk_init()

# Gather sources that live in this folder (main, synth, screens, midi-impl, etc.)
file(GLOB FW_SOURCES CONFIGURE_DEPENDS
    *.c
)

add_executable(pico-synth
    ${FW_SOURCES}
    # If you prefer explicit listing, replace the GLOB above with files here.
)

# TinyUSB quirk from original build
target_compile_definitions(tinyusb_device INTERFACE
    TUD_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX=1
)

# StdIO selection (UART default); switch to USB by enabling the USB line and disabling UART
pico_enable_stdio_uart(pico-synth 1)
# pico_enable_stdio_usb(pico-synth 1)

# Pull in sub-libraries
add_subdirectory(engine)
add_subdirectory(midi)
add_subdirectory(tui)
# New features module (must exist; remove if not using features)
add_subdirectory(features)

# Link everything using the keyword signature (no mixing between keyword/plain)
target_link_libraries(pico-synth
    PRIVATE
        pico_stdlib
        pico_multicore
        hardware_clocks
        hardware_i2c
        hardware_uart
        hardware_pio
        pico_synth_engine
        pico_synth_midi
        pico_synth_tui
        pico_synth_features
)

# Produce .uf2/.elf/.map
pico_add_extra_outputs(pico-synth)
