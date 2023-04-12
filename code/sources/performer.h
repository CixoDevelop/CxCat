#ifndef PERFORMER_H_INCLUDED
#define PERFORMER_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cx/aiko.h>
#include <cx/avrroutine.h>
#include "signals.h"

/** \enum emotions_e emotions_t
 * This is enum that store current emotion.
 */
typedef enum emotions_e {
    
    /* That mean happy state */
    HAPPY = 0,

    /* That mean sad state */
    SAD = 1

} emotions_t;

/** \enum direction_e direction_t
 * This is enum that store current direction platform is moving.
 */
typedef enum direction_e {
    
    /* Platform is staying */
    STOP = 0,

    /* Platform is going to back */
    BACKWARD = 1,

    /* Platform is going forward */
    FORWARD = 2,

    /* Platform is going forward and left */
    FORWARD_LEFT = 3,

    /* Platform is going forward and right */
    FORWARD_RIGHT = 4,
    
    /* Platform is going backward and left */
    BACKWARD_LEFT = 5,

    /* Platform is going backward and right */
    BACKWARD_RIGHT = 6,

    /* Platform is turning left in place */
    ROTATE_LEFT = 7,

    /* Platform is turning right in place */
    ROTATE_RIGHT = 8

} direction_t;

/** \def DIRECTION_MIN
 * This is minimum normal number from direction_e enum, for quick checking
 * correctness in API.
 */
#define DIRECTION_MIN 0

/** \def DIRECTION_MAX 
 * This is maximum normal number from direction_e enum, for quick checking 
 * correctness in API.
 */
#define DIRECTION_MAX 8

/** \typedef control_mode_e control_mode_t 
 * This is enum to define mode of the control.
 */
typedef enum control_mode_e {

    /* This mean, platform is controled by api */
    CONTROL_BY_API = 0,

    /* This mean, platform is controled by ai */
    CONTROL_BY_AI = 1

} control_mode_t;

/** \def CONTROL_MODE_MIN
 * This is the minimum of control mode enum.
 */
#define CONTROL_MODE_MIN 0

/** \def CONTROL_MODE_MAX
 * This is the max of control mode enum.
 */
#define CONTROL_MODE_MAX 1

/** \struct performer_s performer_t
 * This is performer structure, that store all performer states. Performer is
 * main container, that store all states important for platform, like emotions
 * direction that is moving and other. That also share API over UART to
 * communicate platform with other MCU.
 */
typedef struct performer_s {
    
    /* Emotions state for performer */
    emotions_t emotions;

    /* Direction of platform */
    direction_t direction;
    
    /* Platform control mode */
    control_mode_t control_mode;

} performer_t;

/** \fn performer_create
 * This function setup performer fields with default values.
 * @param *self Performer to work on
 */
void performer_create(performer_t *self);

/** \fn performer_process
 * This process is required for communicate with other MCU via API over UART.
 * @param *kernel Kernel to work in
 * @param *process Process context
 */
void performer_process(kernel_instance_t *kernel, process_t *process);

#endif
