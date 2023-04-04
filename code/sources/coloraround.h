#ifndef COLORAROUND_H_INCLUDED
#define COLORAROUND_H_INCLUDED

#include <stdint.h>
#include <avr/pgmspace.h>
#include <cx/avrroutine.h>
#include <cx/colorstripe.h>
#include <cx/aiko.h>
#include "signals.h"
#include "performer.h"

/** \struct coloraround_s coloraround_t
 * This struct store all field required by coloraround to animate it with
 * states shared by performer.
 */
typedef struct coloraround_s {
    
    /* Hardware to show states on */
    colorstripe_t *hardware;

    /* Animations array */
    color_t (* const *animations)(unsigned int, unsigned int);
    
    /* Performer to get states from it */
    performer_t *performer;

} coloraround_t;

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
);

/** \fn coloraround_process
 * This process get appropriate animations and show it on hardware.
 * @param *kernel Kernel to work in it
 * @param *process Process context
 */
void coloraround_process(kernel_instance_t *kernel, process_t *process);

#endif
