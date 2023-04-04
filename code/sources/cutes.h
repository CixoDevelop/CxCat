#ifndef CUTES_H_INCLUDED
#define CUTES_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <cx/avrroutine.h>
#include <cx/aiko.h>
#include "performer.h"
#include "signals.h"

/** \struct cutes_s cutes_t
 * This is type for cutes, that store all required pointers to work with
 * cutes.
 */
typedef struct cutes_s {
    
    /* Hardware to show state on it */
    shift_register_t *hardware;

    /* Animations array to get next states from it */
    uint8_t *animations;

    /* Size of single animation array */
    uint8_t size;

    /* Current animation position */
    uint8_t count;

    /* Performer to get states from that */
    performer_t *performer;

} cutes_t;

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
);

/** \fn cutes_process
 * This is aiko process for controling cutes eyes. That change frame showing
 * on leds, to next every CUTES_TIMEOUT event.
 * @param *kernel Kernel currently running
 * @param *process Context of running process
 */
void cutes_process(kernel_instance_t *kernel, process_t *process);

#endif
