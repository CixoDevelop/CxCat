#include <stdint.h>
#include <stdbool.h>
#include "software_timer.h"

/** \var software_timer_state
 * This var store current state of software timer.
 */
uint16_t software_timer_state;

/** \fn software_timer_set 
 * This set software timer to given time.
 * @param time Time to set
 */
void software_timer_set(uint16_t time) {
    software_timer_state = time;
}

/** \fn software_timer_left
 * This return timer state. When timer left, then it is true, when not
 * false.
 * @return True when timer left, false when not
 */
bool software_timer_left() {
    return software_timer_state == 0;
}

/** \fn software_timer_feed
 * This function is useable to feed software timer. That function tell 
 * that, part of time left.
 */
void software_timer_feed() {
    if (software_timer_state > 0) --software_timer_state;
}
