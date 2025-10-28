# SPDX-FileCopyrightText: 2021-2022 Rafael G. Martins
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-synth C CXX ASM)

pico_sdk_init()

add_executable(pico-synth
    main.c

    eeprom-types.h

    midi-impl.c
    midi-notif.c
    midi-notif.h

    screen-main.c
    screen-main.h
    screen-settings.c
    screen-settings.h
    screen-settings-channel.c
    screen-settings-channel.h
    screen-settings-channel-midi.c
    screen-settings-channel-midi.h
    screen-settings-channel-preset.c
    screen-settings-channel-preset.h
    screen-settings-channels.c
    screen-settings-channels.h
    screen-settings-eeprom-erase.c
    screen-settings-eeprom-erase.h
    screen-settings-eeprom-error.c
    screen-settings-eeprom-error.h
    screen-settings-eeprom-updating.c
    screen-settings-eeprom-updating.h
    screen-settings-preset.c
    screen-settings-preset.h
    screen-settings-preset-adsr-attack.c
    screen-settings-preset-adsr-attack.h
    screen-settings-preset-adsr-decay.c
    screen-settings-preset-adsr-decay.h
    screen-settings-preset-adsr-release.c
    screen-settings-preset-adsr-release.h
    screen-settings-preset-adsr-sustain.c
    screen-settings-preset-adsr-sustain.h
    screen-settings-preset-waveform.c
    screen-settings-preset-waveform.h
    screen-settings-presets.c
    screen-settings-presets.h
    screen-splash.c
    screen-splash.h

    # New features screen
    screen-features.c
    screen-features.h

    synth.c
    synth.h
    synth-data.h
)

# Link using keyword signature only
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

# TinyUSB quirk (already present in downstream)
target_compile_definitions(tinyusb_device INTERFACE
    TUD_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX=1
)

pico_enable_stdio_uart(pico-synth 1)
pico_add_extra_outputs(pico-synth)

add_subdirectory(engine)
add_subdirectory(midi)
add_subdirectory(tui)
add_subdirectory(features)
