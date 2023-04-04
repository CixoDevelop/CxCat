#include <cx/aiko.h>
#include <cx/avrroutine.h>
#include "performer.h"
#include "driver.h"

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
) {
    self->left = left;
    self->right = right;
    self->performer = performer;
}

/** \fn platform_driver_process
 * This is platform driver routine. That check platform and performer state 
 * and change directions of engines.
 * @param *kernel Kernel to work in
 * @param *process Process context
 */
void platform_driver_process(kernel_instance_t *kernel, process_t *process) {
    platform_driver_t *self = process->parameter;

    switch (self->performer->direction) {
        case STOP:
            driver_stop_engine(self->left);
            driver_stop_engine(self->right);
            return;

        case BACKWARD:
            driver_move_backward(self->left);
            driver_move_backward(self->right);
            return;

        case FORWARD:
            driver_move_forward(self->left);
            driver_move_forward(self->right);
            return;

        case FORWARD_LEFT:
            driver_stop_engine(self->left);
            driver_move_forward(self->right);
            return;

        case FORWARD_RIGHT:
            driver_move_forward(self->left);
            driver_stop_engine(self->right);
            return;

        case BACKWARD_LEFT:
            driver_stop_engine(self->left);
            driver_move_backward(self->right);
            return;

        case BACKWARD_RIGHT:
            driver_move_backward(self->left);
            driver_stop_engine(self->right);
            return;
        
        case ROTATE_LEFT:
            driver_move_backward(self->left);
            driver_move_forward(self->right);
            return;

        case ROTATE_RIGHT:
            driver_move_forward(self->left);
            driver_move_backward(self->right);
            return;
    }
}
