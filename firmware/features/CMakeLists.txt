# CMake for pico_synth_features
# Drop this file into: firmware/features/CMakeLists.txt

add_library(pico_synth_features STATIC
    features.c
    feature_midi_monitor.c
)

# Headers from this dir + TUI + MIDI public headers
target_include_directories(pico_synth_features PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../tui/include
    ${CMAKE_CURRENT_LIST_DIR}/../midi/include
)

# Pull in SDK include paths so headers like <hardware/uart.h> resolve
target_link_libraries(pico_synth_features PUBLIC
    pico_stdlib
)
