#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cx/aiko.h>
#include <cx/avrroutine.h>
#include "performer.h"
#include "signals.h"

/** \fn performer_create
 * This function setup performer fields with default values.
 * @param *self Performer to work on
 */
void performer_create(performer_t *self) {
    self->emotions = HAPPY;
    self->direction = STOP;
}

/** \fn performer_process
 * This process is required for communicate with other MCU via API over UART.
 * @param *kernel Kernel to work in
 * @param *process Process context
 */
void performer_process(kernel_instance_t *kernel, process_t *process) {
    performer_t *self = process->parameter;
    uint_t signal = (uintptr_t)message_box_receive(process->message);
    
    if (!(signal & SERIAL_RECEIVED_SIGNAL)) return;
    
    char *serial = serial_get_received_buffer();
    char last_received = serial_get_last_received();
    
    serial_write_char(last_received);
    
    if (last_received == '\r' || last_received  == '\n') {
        serial_received_buffer_flush();
        return;
    }
    
    switch (serial[0]) {
        case 'E':
            if (serial[1] == 'h') self->emotions = HAPPY;
            if (serial[1] == 's') self->emotions = SAD;
            return;
            
        case 'D':
            char direction = serial[1] - '0';

            if (direction < DIRECTION_MIN || direction > DIRECTION_MAX) {
                return;
            }

            self->direction = direction;
            return;
    }
}
