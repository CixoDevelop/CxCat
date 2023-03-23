#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <aiko.h>
#include <stdavr.h>
#include <colorstripe.h>
#include "emotions.h"
#include "performer.h"
#include "signals.h"
#include "head.h"
#include "times.h"

kernel_instance_t kernel[1];

ISR(TIMER_TIMEOUT) {
    static uint8_t more_time = 0;
    uint8_t signal = ANIMATION_TIMEOUT_SIGNAL;

    if (more_time == 0) signal |= HEAD_TIMEOUT_SIGNAL;
    if (more_time == 0) more_time = HEAD_TIME_SCALE; else --more_time;

    kernel_trigger_signal(kernel, signal);
}

int main() {
    /* Hardware objects */
    driver_t left[1];
    driver_t right[1];
    shift_register_t head_register[1];
    colorstripe_t stripe[1];

    /* Init hardware */
    shift_register_create(head_register, PIN_17, PIN_18, PIN_19);
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
  
    /* Prepare robot performer */
    performer_t performer[1];

    performer_create(performer);
    kernel_create_process(
        kernel,
        kernel_get_empty_pid(kernel),
        SIGNAL,
        performer_process, 
        performer
    );

    /* Prepare head */
    head_t head[1];

    head_create(head, head_register, performer);
    kernel_create_process(
        kernel,
        kernel_get_empty_pid(kernel),
        SIGNAL,
        head_process,
        head
    );

    /* Set timer */
    timer_enable();
    timer_set_timeout(TIMER_CALC(0));

    /* Init serial */
    serial_init(BUADRATE(38400));

    /* Ready to go */
    kernel_scheduler(kernel);

    while (true);

    return 0;
}
