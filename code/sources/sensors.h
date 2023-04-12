#ifndef SENSORS_H_INCLUDED
#define SENSORS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <cx/aiko.h>
#include <cx/avrroutine.h>

/** \typedef sensor_state_e sensor_state_t
 * This is useanble to store current state of sensor.
 */
typedef enum sensors_state_e {
    
    /* Sensor is triggered */
    TRIGGERED = true,

    /* This mean sensors is not triggered */
    UNTRIGGERED = false

} sensor_state_t;

/** \typedef sensors_news_e sensors_news_t
 * This store new sensors event.
 */
typedef enum sensors_news_e {
   
    /* Any sensors is not triggered */
    SENSORS_NOT_TRIGGERED = 0b00,

    /* Left sensor is triggered */
    LEFT_SENSOR_TRIGGERED = 0b01,

    /* Rigth sensor is triggered */
    RIGHT_SENSOR_TRIGGERED = 0b10,

    /* Both of sensors are triggered */
    BOTH_SENSORS_TRIGGERED = 0b11

} sensors_news_t;

/** \def LEFT_SENSOR_TRIGGERED_BITS_POSITION
 * This store how much bits must be move left, to go into left sensor
 * flag position in sensors_news_t.
 */
#define LEFT_SENSOR_TRIGGERED_BITS_POSITION 0

/** \def LEFT_SENSOR_TRIGGERED_BITS_POSITION
 * This store how much bits must be move left, to go into left sensor
 * flag position in sensors_news_t.
 */
#define RIGHT_SENSOR_TRIGGERED_BITS_POSITION 1

/** \struct sensors_s sensors_t 
 * This is struct, that store content required to monitor sensors state, and
 * change state after any change.
 */
typedef struct sensors_s {

    /* Left sensor pin */
    pin_t left_sensor;
    
    /* Right sensor pin */
    pin_t right_sensor;

    /* Platform controller process */
    kernel_pid_t platform_controller;

    /* Left sensor state */
    sensor_state_t left_state;

    /* Right sensor state */
    sensor_state_t right_state;

} sensors_t;

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
);

/** \fn sensors_process
 * On default for this plarform Atmega 8 not be any pinchange interrupts. 
 * Sensors must be monitored, and software must make interrupt when detect
 * any changes.
 * @param *kernel Kernel to work in
 * @param *process Process context
 */
void sensors_process(kernel_instance_t *kernel, process_t *process);

#endif
