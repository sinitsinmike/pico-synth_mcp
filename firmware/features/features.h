#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <pico-synth/tui.h>
#include <pico-synth/midi.h>

typedef struct {
    const char *name;
    bool enabled;
    void (*init)(ps_tui_t *tui, void *ctx);
    void (*tick_core0)(ps_tui_t *tui, void *ctx);
    void (*on_midi)(ps_tui_t *tui, void *ctx, const ps_midi_message_t *msg);
} ps_feature_t;

void ps_features_init(ps_tui_t *tui, void *ctx);
void ps_features_tick(ps_tui_t *tui);
void ps_features_on_midi(ps_tui_t *tui, const ps_midi_message_t *msg);
size_t ps_features_count(void);
const ps_feature_t* ps_features_get(size_t idx);
void ps_features_toggle(size_t idx);
void ps_features_open_menu(ps_tui_t *tui);
