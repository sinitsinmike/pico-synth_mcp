// firmware/tui/include/pico-synth/tui.h
#pragma once

#include <stdbool.h>
#include <stdint.h>

/* Optional project define kept for compatibility */
#ifndef PS_TUI_EEPROM_BACKLOG_SIZE
#define PS_TUI_EEPROM_BACKLOG_SIZE 1024
#endif

/* Forward alias */
typedef struct ps_tui ps_tui_t;

/* Long-press callback */
typedef void (*ps_tui_long_press_cb_t)(ps_tui_t *tui);

/* Encoder actions */
typedef enum {
    PS_TUI_ENCODER_ACTION_BUTTON = 1,
    PS_TUI_ENCODER_ACTION_ROTATE_CW,
    PS_TUI_ENCODER_ACTION_ROTATE_CCW,
    PS_TUI_ENCODER_ACTION_BUTTON_LONG, /* added */
} ps_tui_encoder_action_t;

/* OLED text alignment (kept minimal; extend if needed) */
typedef enum {
    PS_TUI_OLED_HALIGN_LEFT = 0,
    PS_TUI_OLED_HALIGN_CENTER,
    PS_TUI_OLED_HALIGN_RIGHT,
} ps_tui_oled_halign_t;

/* Forward declarations */
struct ps_tui_screen;
typedef struct ps_tui_screen ps_tui_screen_t;

typedef struct {
    void (*render_func)(ps_tui_t *tui);
    void (*encoder_func)(ps_tui_t *tui, ps_tui_encoder_action_t act);
} ps_tui_screen_func_t;

/* ---- Main TUI struct (named, not anonymous; no typedef at end) ---- */
struct ps_tui {
    /* I2C bus for OLED, etc. */
    struct {
        void *i2c;         /* opaque pointer to i2c_inst_t */
        uint32_t basepin;  /* SCL pin; SDA assumed basepin+1 in code */
        uint32_t baudrate; /* optional; caller may set */
    } i2c;

    /* EC11 encoder */
    struct {
        uint32_t button;
        uint32_t a;
        uint32_t b;
        uint64_t button_debounce_us;
        uint64_t rotate_debounce_us;

        /* long-press support */
        uint64_t button_long_us;       /* threshold (us), 0 = disabled */

        /* private runtime state (used by driver-ec11.c) */
        uint64_t _button_hit;
        uint64_t _rotate_hit;
        uint8_t  _rotate_state;
        bool     _a_value;
        bool     _b_value;

        /* long-press private state */
        uint64_t _button_down_since;
        bool     _long_sent;
    } encoder;

    /* Free-form user context */
    void *ctx_data;

    /* Global long-press handler */
    ps_tui_long_press_cb_t on_long_press;

    /* Navigation / screen state */
    uint8_t _selected;
    uint8_t _selected_line;
    const ps_tui_screen_t *_current_screen;
    uint64_t _current_screen_us;
};

/* ---- Public API ---- */
int  ps_tui_init(ps_tui_t *tui);
int  ps_tui_task(ps_tui_t *tui);
void ps_tui_screen_load(ps_tui_t *tui, const ps_tui_screen_t *scr);
void ps_tui_screen_reload(ps_tui_t *tui, const ps_tui_screen_t *scr);

/* Minimal OLED helpers used across screens */
void ps_tui_oled_clear(ps_tui_t *tui);
void ps_tui_oled_line(ps_tui_t *tui, uint8_t row, const char *text, ps_tui_oled_halign_t align);

/* Encoder driver callback entry */
void ec11_callback(ps_tui_t *tui, ps_tui_encoder_action_t act);
