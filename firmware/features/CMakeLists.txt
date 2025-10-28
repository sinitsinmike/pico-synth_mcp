# firmware/features/CMakeLists.txt (drop-in)
# Build features as a plain STATIC library with only its own sources.
add_library(pico_synth_features STATIC
    features.c
    features-config.h
    feature_midi_monitor.c
)

# Expose local and dependent public headers (tui/midi)
target_include_directories(pico_synth_features
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../tui/include
        ${CMAKE_CURRENT_LIST_DIR}/../midi/include
)

# Minimal link to pull in SDK include dirs (NO TUI/MIDI link here!)
# This avoids dragging object sources from those libs into this target.
target_link_libraries(pico_synth_features
    PUBLIC
        pico_stdlib
        hardware_uart
)
