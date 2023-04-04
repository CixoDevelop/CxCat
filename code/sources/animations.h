#ifndef ANIMATIONS_H_INCLUDED
#define ANIMATIONS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <colorstripe.h>
#include <avr/pgmspace.h>

/** \def XXX_EYE
 * This defines eyes states in cutes to use in animations.
 */
#define BIG_EYE (0xCF)
#define SMALL_EYE (0xFF ^ 0xCF)
#define ALL_EYE (SMALL_EYE | BIG_EYE)
#define CLOSE_EYE (0x00)

/** \var cutes_animations
 * This store animations for cutest, for all avairable performer emotions
 * state. This is stored in PROGMEM!
 */
extern uint8_t const cutes_animations[2][5];

/** \var coloraround_animations
 * This store animations for coloraround. Animations for this is colorstripe
 * compatible functions, and this variable is array of pointers to that 
 * functions. This is stored in PROGMEM!
 */
extern color_t (* const coloraround_animations[2])(
    unsigned int, 
    unsigned int
);

/** \fn coloraround_animation_happy
 * This is coloradound animation, colorstripe compatible, for show performer 
 * is happy.
 * @param count That is current calculated led number
 * @param lenght That is stripe lenght
 * @return Calculated color
 */
color_t coloraround_animation_happy(unsigned int count, unsigned int lenght);

/** \fn coloraround_animation_happy
 * This is coloradound animation, colorstripe compatible, for show performer 
 * is sad.
 * @param count That is current calculated led number
 * @param lenght That is stripe lenght
 * @return Calculated color
 */
color_t coloraround_animation_sad(unsigned int count, unsigned int lenght);

#endif
