#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdint.h>
#include <stdavr.h>
#include <aiko.h>
#include "performer.h"
#include "signals.h"

typedef struct head_s {
    uint8_t state;
    performer_t *performer;
    shift_register_t *hardware;
} head_t;

uint8_t head_animations[4][2] = {
    {0xFF, 0x00},
    {0xF0, 0x0F},
    {0x11, 0x00},
    {0xAA, 0xBB}
};

void head_create(
    head_t *self, 
    shift_register_t *hardware, 
    performer_t *performer
) {
    self->hardware = hardware;
    self->performer = performer;
    self->state = 0;

    shift_register_send(hardware, 0x00, true);
}

void head_process(kernel_instance_t *kernel, process_t *process) {
    uint_t signal = (uintptr_t)message_box_receive(process->message);
    head_t *self = (head_t*)process->parameter;
    
    if (!(signal & HEAD_TIMEOUT_SIGNAL)) return;

    ++self->state;

    if (self->state == sizeof(head_animations[0])) self->state = 0x00;

    shift_register_send(
        self->hardware,
        head_animations[self->performer->state][self->state],
        true
    );
}

#endif
