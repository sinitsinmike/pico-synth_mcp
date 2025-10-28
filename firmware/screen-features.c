#include <stdio.h>
#include "features/features.h"
#include <pico-synth/tui.h>
#include "screen-features.h"

static uint8_t sel = 0;

static void render(ps_tui_t *tui) {
    ps_tui_oled_clear(tui);
    ps_tui_oled_line(tui, 0, "Features", PS_TUI_OLED_HALIGN_CENTER);
    uint8_t n = (uint8_t) ps_features_count();
    uint8_t max = n > 6 ? 6 : n;
    for (uint8_t i = 0; i < max; ++i) {
        const ps_feature_t *f = ps_features_get(i);
        if (!f) continue;
        char line[22];
        snprintf(line, sizeof(line), "%c %s [%s]",
                 (i == sel) ? 0x10 : ' ',
                 f->name,
                 f->enabled ? "ON" : "OFF");
        ps_tui_oled_line(tui, i + 2, line, PS_TUI_OLED_HALIGN_LEFT);
    }
}

static void encoder(ps_tui_t *tui, ps_tui_encoder_action_t act) {
    switch (act) {
        case PS_TUI_ENCODER_ACTION_ROTATE_CW:
            if (sel + 1 < ps_features_count() && sel < 5) sel++;
            break;
        case PS_TUI_ENCODER_ACTION_ROTATE_CCW:
            if (sel > 0) sel--;
            break;
        case PS_TUI_ENCODER_ACTION_BUTTON:
            ps_features_toggle(sel);
            break;
        default: break;
    }
    ps_tui_screen_reload(tui, &screen_features);
}

static const ps_tui_screen_func_t func = {
    .render_func = render,
    .encoder_func = encoder,
};

const ps_tui_screen_t screen_features = {
    .type = PS_TUI_SCREEN_FUNC,
    .func = &func,
};

void ps_features_open_menu(ps_tui_t *tui) {
    sel = 0;
    ps_tui_screen_load(tui, &screen_features);
}
