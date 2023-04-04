#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cx/aiko.h>
#include <cx/avrroutine.h>
#include <cx/colorstripe.h>
#include "cutes.h"
#include "signals.h"
#include "times.h"
#include "coloraround.h"
#include "animations.h"
#include "driver.h"

/** \var kernel
 * This is kernel instance. This is global, to use it in ISR routines.
 */
kernel_instance_t kernel[1];

/** \fn ISR_TIMER_TIMEOUT
 * This is ISR routine to handle timer timeout. That is used to trigger frame
 * signals for both of animated elements, that mean coloraround and cutes. It
 * have simple algorith to divide clock, and trigger cutes every few 
 * coloraround, because coloraround have higher framerate.
 */
ISR(TIMER_TIMEOUT) {
    static uint8_t more_time = 0;
    
    kernel_sum_signal(kernel, COLORAROUND_TIMEOUT_SIGNAL);

    if (more_time == 0) kernel_sum_signal(kernel, CUTES_TIMEOUT_SIGNAL);
    if (more_time == 0) more_time = CUTES_FRAME_SCALE; else --more_time;

    timer_set_timeout(TIMER_CALC(COLORAROUND_FRAME_TIME));
}

/** \fn serial_received_signal_trigger
 * That is callback which serial trigger every received char. That simple 
 * triggger signal in operating system, to notify processes which waiting 
 * for it
 */
void serial_received_signal_trigger() {
    kernel_sum_signal(kernel, SERIAL_RECEIVED_SIGNAL);
}

/** \fn main
 * That is main function in project.
 * @return 0
 */
int main() {
    /* Hardware objects */
    driver_t left[1];
    driver_t right[1];
    shift_register_t cutes_register[1];
    colorstripe_t stripe[1];

    /* Init hardware */
    shift_register_create(cutes_register, PIN_17, PIN_18, PIN_19);
    driver_create(left, PIN_23, PIN_24, PIN_25);
    driver_create(right, PIN_26, PIN_27, PIN_28);
    colorstripe_init(stripe, ws2812b_sender, PIN_6, 7);

    driver_stop_engine(left);
    driver_stop_engine(right);

    /* Operating system prepare */
    process_t kernel_area[5];
    kernel_create_static(
        kernel,
        kernel_area,
        sizeof(kernel_area) / sizeof(process_t)
    );

    /* Init performer */
    performer_t performer[1];
    performer_create(performer);
    kernel_create_process(
        kernel,
        kernel_get_empty_pid(kernel),
        SIGNAL,
        performer_process,
        performer
    );
    
    /* Init cutes */
    cutes_t cutes[1];
    cutes_create(
        cutes, 
        cutes_register, 
        (uint8_t *)cutes_animations, 
        sizeof(cutes_animations[0]) / sizeof(cutes_animations[0][0]),
        performer
    );
    kernel_create_process(
        kernel,
        kernel_get_empty_pid(kernel),
        SIGNAL,
        cutes_process,
        cutes
    );
    
    /* Init coloraround */
    coloraround_t coloraround[1];
    coloraround_create(
        coloraround, 
        stripe, 
        coloraround_animations, 
        performer
    );
    kernel_create_process(
        kernel,
        kernel_get_empty_pid(kernel), 
        SIGNAL,
        coloraround_process,
        coloraround
    );

    /* Init platform driver */
    platform_driver_t platform_driver[1];
    platform_driver_create(
        platform_driver,
        left,
        right,
        performer
    );
    kernel_create_process(
        kernel,
        kernel_get_empty_pid(kernel),
        CONTINUOUS,
        platform_driver_process,
        platform_driver
    );

    /* Init timer */
    timer_enable();
    timer_set_timeout(TIMER_CALC(0));

    /* Init serial */
    serial_init(BUADRATE(9600));
    serial_set_received_callback(serial_received_signal_trigger);

    /* Start main loop */
    kernel_scheduler(kernel);

    /* Any critical error occured */
    while (true) __asm__("nop");

    return 0;
}
