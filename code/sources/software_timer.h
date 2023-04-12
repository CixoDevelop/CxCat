#ifndef SOFTWARE_TIMER_H_INCLUDED
#define SOFTWARE_TIMER_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

/** \fn software_timer_set 
 * This set software timer to given time.
 * @param time Time to set
 */
void software_timer_set(uint16_t time);

/** \fn software_timer_left
 * This return timer state. When timer left, then it is true, when not
 * false.
 * @return True when timer left, false when not
 */
bool software_timer_left();

/** \fn software_timer_feed
 * This function is useable to feed software timer. That function tell 
 * that, part of time left.
 */
void software_timer_feed();

#endif
