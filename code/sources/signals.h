#ifndef SIGNALS_H_INCLUDED
#define SIGNALS_H_INCLUDED

/** \def COLORAROUND_TIMEOUT_SIGNAL
 * This signal is triggered when coloraround will show next animation frame.
 */
#define COLORAROUND_TIMEOUT_SIGNAL 0b00000001

/** \def COLLISION_SENSOR_SIGNAL
 * This signal is triggered when collision sensor detect new event.
 */
#define COLLISION_SENSOR_SIGNAL 0b00000010

/** \def CUTES_TIMEOUT_SIGNAL
 * This signal is triggered when cutes will show next animation frame.
 */
#define CUTES_TIMEOUT_SIGNAL 0b00000100

/** \def SERIAL_RECEIVED_SIGNAL
 * This signal is triggered when serial receive new data.
 */
#define SERIAL_RECEIVED_SIGNAL 0b00001000

#endif
