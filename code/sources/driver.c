#include <cx/aiko.h>
#include <cx/avrroutine.h>
#include "performer.h"
#include "driver.h"
#include "sensors.h"

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

void platform_driver_set_direction_api(
    platform_driver_t *self, 
    direction_t direction
) {
    switch (direction) {
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

void platform_driver_control_ai(
    platform_driver_t *self,
    sensors_news_t news
) { 

}

/** \fn platform_driver_process
 * This is platform driver routine. That check platform and performer state 
 * and change directions of engines.
 * @param *kernel Kernel to work in
 * @param *process Process context
*/
void platform_driver_process(kernel_instance_t *kernel, process_t *process) {
    platform_driver_t *self = process->parameter;
    sensors_news_t news = SENSORS_NOT_TRIGGERED;

    if (message_box_is_sendable(process->message)) {
        news = (uint8_t)(uintptr_t)(message_box_receive(process->message));
    }

    if (self->performer->control_mode == CONTROL_BY_API) {
        platform_driver_set_direction_api(self, self->performer->direction);
        return;
    }

    platform_driver_control_ai(self, news);
}
