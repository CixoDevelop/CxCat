#ifndef EYES_H_INCLUDED
#define EYES_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

typedef enum eye_state_e {
    EYE_CLOSE,
    EYE_WIDE_OPEN,
    EYE_LOOKING_RIGHT,
    EYE_LOOKING_LEFT,
    EYE_LOOKING_CENTER
} eye_state_t;

typedef struct eye_s {
    eye_state_t state;
    uint8_t bits[4];
} eye_t;



#endif
