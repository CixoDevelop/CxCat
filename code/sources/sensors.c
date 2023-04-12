#include <stdint.h>
#include <stdbool.h>
#include <cx/aiko.h>
#include <cx/avrroutine.h>
#include "sensors.h"

/** \fn sensors_create
 * This function create and initialise new sensors structure. That is useable
 * to recognise platform colisions.
 * @param *self Sensors struct to work on
 * @param left_sensor Left sensor pin
 * @param right_sensor Right sensor pin
 * @param platform_controller Platform controller PID
 */
void sensors_create(
    sensors_t *self, 
    pin_t left_sensor, 
    pin_t right_sensor,
    kernel_pid_t platform_controller
) {
    self->left_sensor = left_sensor;
    self->right_sensor = right_sensor;
    self->platform_controller = platform_controller;
    self->left_state = UNTRIGGERED;
    self->right_state = UNTRIGGERED;

    pin_set_mode(left_sensor, INPUT);
    pin_set_mode(right_sensor, INPUT);
}

/** \fn sensors_process
 * On default for this plarform Atmega 8 not be any pinchange interrupts. 
 * Sensors must be monitored, and software must make interrupt when detect
 * any changes.
 * @param *kernel Kernel to work in
 * @param *process Process context
 */
void sensors_process(kernel_instance_t *kernel, process_t *process) {
    sensors_t *self = process->parameter;
   
    
    sensor_state_t left_state = (pin_get_state(self->left_sensor) == LOW);
    sensor_state_t right_state = (pin_get_state(self->right_sensor) == LOW);

    sensor_state_t left_flag = (
        left_state && (left_state != self->left_state)
    );
    
    sensor_state_t right_flag = (
        right_state && (right_state != self->right_state)
    );

    left_flag <<= LEFT_SENSOR_TRIGGERED_BITS_POSITION;
    right_flag <<= RIGHT_SENSOR_TRIGGERED_BITS_POSITION;

    sensors_news_t state = (left_flag | right_flag);

    if (state) kernel_process_message_box_send(
        kernel,
        self->platform_controller, 
        (void *)(uintptr_t)state
    );
}
