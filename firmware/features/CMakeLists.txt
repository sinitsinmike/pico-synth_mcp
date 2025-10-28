# Features module built as a STATIC library.
# Do not link TUI or pico_stdlib here to avoid INTERFACE_SOURCES being
# compiled inside this target. The final executable links everything.

add_library(pico_synth_features STATIC
    features.c
    features-config.h
    feature_midi_monitor.c
)

# Public headers for dependent targets
target_include_directories(pico_synth_features
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../tui/include
        ${CMAKE_CURRENT_LIST_DIR}/../midi/include
)

# Intentionally NO target_link_libraries here; the executable links TUI/MIDI/SDK.
