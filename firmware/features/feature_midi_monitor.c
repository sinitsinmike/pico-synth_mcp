#include <stdio.h>
#include "feature_midi_monitor.h"

static void on_midi(ps_tui_t *tui, void *ctx, const ps_midi_message_t *msg) {
    (void)tui; (void)ctx;
    if (!msg) return;
    if (msg->group == PS_MIDI_MESSAGE_GROUP_CHANNEL &&
        msg->channel.type == PS_MIDI_MESSAGE_TYPE_CHANNEL_NOTE_ON) {
        printf("[MIDI] ch=%u NOTE_ON %u vel=%u\n",
               msg->channel.channel, msg->channel.data[0], msg->channel.data[1]);
    }
}

const ps_feature_t feature_midi_monitor = {
    .name = "MIDI Monitor",
    .enabled = false,
    .init = NULL,
    .tick_core0 = NULL,
    .on_midi = on_midi,
};
