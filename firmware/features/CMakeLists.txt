add_library(pico_synth_features
    features.c
    features-config.h
    feature_midi_monitor.c
)

# Public include dirs so <pico-synth/tui.h> and <pico-synth/midi.h> resolve
target_include_directories(pico_synth_features
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../tui/include
        ${CMAKE_CURRENT_LIST_DIR}/../midi/include
)

# Link against the libraries that export those headers/APIs
target_link_libraries(pico_synth_features
    PUBLIC
        pico_stdlib
        pico_synth_tui
        pico_synth_midi
)
