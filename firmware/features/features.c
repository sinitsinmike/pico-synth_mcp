#include "features.h"
#include "features-config.h"

#define DECLARE_FEATURE(name) extern const ps_feature_t name;
PS_FEATURES(DECLARE_FEATURE)

static const ps_feature_t* const g_all[] = {
#define ADD_FEATURE(name) &name,
PS_FEATURES(ADD_FEATURE)
#undef ADD_FEATURE
};
static const size_t g_all_n = sizeof(g_all)/sizeof(g_all[0]);
static void *g_ctx = NULL;

void ps_features_init(ps_tui_t *tui, void *ctx) {
    (void)tui;
    g_ctx = ctx;
    for (size_t i = 0; i < g_all_n; ++i)
        if (g_all[i]->enabled && g_all[i]->init) g_all[i]->init(tui, ctx);
}

void ps_features_tick(ps_tui_t *tui) {
    for (size_t i = 0; i < g_all_n; ++i)
        if (g_all[i]->enabled && g_all[i]->tick_core0) g_all[i]->tick_core0(tui, g_ctx);
}

void ps_features_on_midi(ps_tui_t *tui, const ps_midi_message_t *msg) {
    for (size_t i = 0; i < g_all_n; ++i)
        if (g_all[i]->enabled && g_all[i]->on_midi) g_all[i]->on_midi(tui, g_ctx, msg);
}

size_t ps_features_count(void) { return g_all_n; }
const ps_feature_t* ps_features_get(size_t idx) { return idx < g_all_n ? g_all[idx] : NULL; }
void ps_features_toggle(size_t idx) {
    if (idx >= g_all_n) return;
    ((ps_feature_t*)g_all[idx])->enabled = !g_all[idx]->enabled;
}
