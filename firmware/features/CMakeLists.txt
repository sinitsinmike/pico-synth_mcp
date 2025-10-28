cmake_minimum_required(VERSION 3.13)

add_library(pico_synth_features
    features.c
    feature_midi_monitor.c
)

target_include_directories(pico_synth_features
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../tui/include
        ${CMAKE_CURRENT_LIST_DIR}/../midi/include
)

# Pull in Pico SDK components so headers like <hardware/i2c.h> resolve during compilation
target_link_libraries(pico_synth_features
    PUBLIC
        pico_stdlib
        hardware_gpio
        hardware_i2c
        hardware_uart
        pico_unique_id
)
