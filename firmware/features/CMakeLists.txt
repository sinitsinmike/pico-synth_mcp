add_library(pico_synth_features
    features.c
    features-config.h
    feature_midi_monitor.c
)
target_include_directories(pico_synth_features PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(pico_synth_features pico_stdlib)
