#ifndef PERFORMER_H_INCLUDED
#define PERFORMER_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <aiko.h>
#include "signals.h"

typedef enum events_e {
    HAPPINESS,
    SADNESS,
    AMUSEMENT,
    SLEEP
} events_t;

typedef struct performer_s {
    uint16_t activity;
    events_t state;
} performer_t;

void performer_create(performer_t *self) {
    self->activity = 0x00;
    self->state = SLEEP;
}

void performer_process(kernel_instance_t *kernel, process_t *process) {
    performer_t *self = process->parameter;
    uint_t signal = message_box_receive(process->message_box);

    if (signal == USER_INTERACTION_SIGNAL) {
        if (self->activity + 1 > self.activity) ++self.activity;
        if (self->state == SLEEP) self->state = AMUSEMENT;
    }

    if (signal == PERFORMER_FRAME_SIGNAL) {
        if (self->activity - 1 > self.activity) {
            self->state = SLEEP;
        } else {
            --self->activity;
        }
    }
}

#endif
