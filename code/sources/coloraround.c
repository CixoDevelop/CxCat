#include <stdint.h>
#include <avr/pgmspace.h>
#include <cx/avrroutine.h>
#include <cx/colorstripe.h>
#include <cx/aiko.h>
#include "coloraround.h"
#include "signals.h"
#include "performer.h"

/** \fn coloraround_create
 * This create new coloraround from given params.
 * @param *self Coloraround to work on it
 * @param *hardware Hardware to work with
 * @param *animations Array with coloraround animations
 * @param *performer Performer to work with it
 */
void coloraround_create(
    coloraround_t *self,
    colorstripe_t *hardware,
    color_t (* const *animations)(unsigned int, unsigned int),
    performer_t *performer
) {
    self->animations = animations;
    self->hardware = hardware;
    self->performer = performer;
}

/** \fn coloraround_process
 * This process get appropriate animations and show it on hardware.
 * @param *kernel Kernel to work in it
 * @param *process Process context
 */
void coloraround_process(kernel_instance_t *kernel, process_t *process) {
    uint_t signal = (uintptr_t)message_box_receive(process->message);
    coloraround_t *self = process->parameter;

    if (!(signal & COLORAROUND_TIMEOUT_SIGNAL)) return;

    color_t (*animation)(unsigned int, unsigned int) = pgm_read_ptr(
        self->animations + self->performer->emotions
    );

    colorstripe_functional_setter(self->hardware, animation);
}
