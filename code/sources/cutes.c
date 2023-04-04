#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <stdavr.h>
#include <aiko.h>
#include "cutes.h"
#include "performer.h"
#include "signals.h"

/** \fn cutes_create
 * This function create and prepare cutes to work. That init cutes struct, and
 * sending blank frame to hardware.
 * @param *self Cutes object to work on
 * @param *hardware Shift register with cutes
 * @param *animations Animations array for cutes
 * @param size Size of cutes array
 * @*performer Pointer to performer, from it income current emotions state
 */
void cutes_create(
    cutes_t *self, 
    shift_register_t *hardware,
    uint8_t *animations, 
    uint8_t size,
    performer_t *performer
) {
    self->hardware = hardware;
    self->animations = animations;
    self->size = size;
    self->performer = performer;
    self->count = 0x00;
}

/** \fn cutes_process
 * This is aiko process for controling cutes eyes. That change frame showing
 * on leds, to next every CUTES_TIMEOUT event.
 * @param *kernel Kernel currently running
 * @param *process Context of running process
 */
void cutes_process(kernel_instance_t *kernel, process_t *process) {
    uint_t signal = (uintptr_t)message_box_receive(process->message);
    cutes_t *self = process->parameter;
    
    if (!(signal & CUTES_TIMEOUT_SIGNAL)) return;
    
    self->count = (self->count + 1) % self->size;
    
    uint8_t *frame = self->animations;
    
    frame += self->size * self->performer->emotions;
    frame += self->count;

    shift_register_send(self->hardware, pgm_read_byte(frame), true);
}
