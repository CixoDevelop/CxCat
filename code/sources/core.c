#include <stdbool.h>
#include <stdavr.h>
#include <stdavr/atmega8.h>
#include <util/delay.h>

int main() {
    driver_t left[1];

    driver_create(left, PIN_12, PIN_13, PIN_14);
    pin_set_mode(PIN_11, OUTPUT);

    while (true) {
        driver_move_forward(left);
        pin_set_state(PIN_11, HIGH);
    
        _delay_ms(500);

        driver_move_backward(left);
        pin_set_state(PIN_11, LOW);

        _delay_ms(500);
    }
    

    while (true) ;
}
