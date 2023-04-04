#include <stdint.h>
#include <stdbool.h>
#include <colorstripe.h>
#include <avr/pgmspace.h>
#include "animations.h"

/** \var cutes_animations
 * This store animations for cutest, for all avairable performer emotions
 * state. This is stored in PROGMEM!
 */
uint8_t const cutes_animations[2][5] PROGMEM = {
    {BIG_EYE, ALL_EYE, BIG_EYE, CLOSE_EYE, SMALL_EYE},
    {SMALL_EYE, BIG_EYE, SMALL_EYE, ALL_EYE, CLOSE_EYE}
};

/** \var coloraround_animations
 * This store animations for coloraround. Animations for this is colorstripe
 * compatible functions, and this variable is array of pointers to that 
 * functions. This is stored in PROGMEM!
 */
color_t (* const coloraround_animations[2])(
    unsigned int, 
    unsigned int
) PROGMEM = {
    coloraround_animation_happy, 
    coloraround_animation_sad
};

/** \fn coloraround_animation_happy
 * This is coloradound animation, colorstripe compatible, for show performer 
 * is happy.
 * @param count That is current calculated led number
 * @param lenght That is stripe lenght
 * @return Calculated color
 */
color_t coloraround_animation_happy(unsigned int count, unsigned int lenght) {
    static unsigned int step = 0;
    static bool direction = false;

    if (count == 0) {
        if (step == 0x00) direction = true;
        if (direction) ++step; else --step;
        if (step == lenght - 1) direction = false;
    }

    if (count == step) return (color_t){0xA9, 0x40, 0x64}; 
    return (color_t){0x00, 0x00, 0x00};
}

/** \fn coloraround_animation_happy
 * This is coloradound animation, colorstripe compatible, for show performer 
 * is sad.
 * @param count That is current calculated led number
 * @param lenght That is stripe lenght
 * @return Calculated color
 */
color_t coloraround_animation_sad(unsigned int count, unsigned int lenght) {
    static uint8_t current = 0x00;

    if (count == 0x00) ++current;
    if (current == lenght) current = 0x00;

    return (color_t){count * current, count + current, count - current};
}
