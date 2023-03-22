#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <aiko.h>
#include <stdavr.h>
#include <colorstripe.h>
#include "emotions.h"

#define ANIMATION_TIMEOUT_SIGNAL 20

kernel_instance_t kernel[1];

ISR(TIMER_TIMEOUT) {
    timer_set_timeout(TIMER_CALC(50));
    kernel_trigger_signal(kernel, ANIMATION_TIMEOUT_SIGNAL);
}

int main() {
    /* Hardware objects */
    driver_t left[1];
    driver_t right[1];
    shift_register_t eyes[1];
    colorstripe_t stripe[1];

    /* Init hardware */
    shift_register_create(eyes, PIN_17, PIN_18, PIN_19);
    driver_create(left, PIN_23, PIN_24, PIN_25);
    driver_create(right, PIN_26, PIN_27, PIN_28);
    colorstripe_init(stripe, ws2812b_sender, PIN_6, 7);

    driver_stop_engine(left);
    driver_stop_engine(right);
    shift_register_send(eyes, 0x00, true);
   
    /* Prepare robot performer */
    

    /* Operating system prepare */
    process_t kernel_area[5];

    kernel_create_static(
        kernel, 
        kernel_area, 
        sizeof(kernel_area) / sizeof(process_t)
    );

    /* Set timer */
    timer_enable();
    timer_set_timeout(TIMER_CALC(0));

    /* Init serial */
    serial_init(BUADRATE(38400));

    kernel_scheduler(kernel);

    while (true);

    return 0;
}
