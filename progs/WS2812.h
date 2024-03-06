/**
 * FILENAME :        WS2812.h          
 *
 * DESCRIPTION :
 *       WS2812 LEDs Strip controller for STM32 (Nucleo Board)
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    24/oct/2023
 *
 *       LEnsE / Institut d'Optique Graduate School
 */

#ifndef     __WS2812_H_HEADER_H__
#define     __WS2812_H_HEADER_H__

#include "mbed.h"

#define WS2812_BUF  5
#define TYPE        24

/* Timing Values */
/* For L476RG :
    T0H = 6, T0L = 13, T1H = 14, T1L = 5
    */

/* BUG : t0h not working... */

/* WS2812B */
/*  T0H = 0.4us / T0L = 0.85us
    T1H = 0.8us / T1L = 0.45us
*/

class WS2812{
    public:
        /**
        * @brief Simple constructor of the WS2812 class.
        * @details Create a WS2812 LEDs Strip controller
        * @param pin_strip Output pin to control the LEDs strip 
        * @param nb_leds Number of LEDs of the strip
        */
        WS2812(PinName pin_strip, int nb_leds);

        /* Setup the timings values */
        void set_timings(int t0h, int t0l, int t1h, int t1l);
        /* Bit of value equal to 1 */
        void send_led_one();
        /* Bit of value equal to 0 */
        void send_led_zero();
        /* Break function between two trames */
        void break_trame();
        /* Send trame to a led */
        void send_led_trame(int cl);
        /* Send a complete trame to nb LEDs on a single strips */
        void send_leds(int *leds);

        /* Blackout */
        void blackout();
    private:
        /* LED Strip output */
        DigitalOut  __ws_led;
        /* Number of LEDs on the strip */
        int         __nb_leds;
        /* Timing for high and low level values */
        int t0h = 0;
        int t0l = 0;
        int t1h = 0;
        int t1l = 0;
        /* */
};

#endif