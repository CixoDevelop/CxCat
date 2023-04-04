#ifndef PLATFORM_DRIVER_H_INCLUDED
#define PLATFORM_DRIVER_H_INCLUDED

#include <aiko.h>
#include <stdavr.h>
#include "performer.h"

/** \struct platform_driver_s platform_driver_t
 * This struct store platform driver, that is required to moving platform.
 */
typedef struct platform_driver_s {

    /* Left engine */
    driver_t *left;

    /* Right engine */
    driver_t *right;

    /* Performer to get direction from */
    performer_t *performer;

} platform_driver_t;

/** \fn platform_driver_create
 * This function create driver.
 * @param *self Driver to work on
 * @param *left Left engine
 * @param *right Right engine
 * @param *performer Platform performer
 */
void platform_driver_create(
    platform_driver_t *self,
    driver_t *left,
    driver_t *right,
    performer_t *performer
);

/** \fn platform_driver_process
 * This is platform driver routine. That check platform and performer state 
 * and change directions of engines.
 * @param *kernel Kernel to work in
 * @param *process Process context
 */
void platform_driver_process(kernel_instance_t *kernel, process_t *process);

#endif
