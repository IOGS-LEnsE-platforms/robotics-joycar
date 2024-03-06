#include "WS2812.h"

/* WS2812B */
/*  T0H = 0.4us / T0L = 0.85us
    T1H = 0.8us / T1L = 0.45us
*/

WS2812::WS2812(PinName pin_strip, int nb_leds):
__ws_led(pin_strip)
{
    this->__ws_led = 0;
    this->__nb_leds = nb_leds;
}

void WS2812::send_led_one(){
    int k;
    this->__ws_led = 1;
    for(k = 0; k < this->t1h; k++)
        __nop();
    this->__ws_led = 0;
    for(k = 0; k < this->t1l; k++)
        __nop();
}

void WS2812::send_led_zero(){
    int k;
    this->__ws_led = 1;  
    for(k = 0; k < 6; k++)  // Attention, pb avec this->t0h !!
        __nop();
    this->__ws_led = 0;
    for(k = 0; k < this->t0l; k++)
        __nop();
}

// Break function
void WS2812::break_trame(){
    this->__ws_led = 0;
    wait_us(100);
}

void WS2812::send_led_trame(int cl){
    for(int k = 0; k < TYPE; k++){
        int bin = cl >> (TYPE-1-k);
        if((bin & 0x1) == 1){
            this->send_led_one();
        }else{
            this->send_led_zero();
        }
    }
}

void WS2812::send_leds(int *leds){
    __disable_irq();
    for(int k = 0; k < this->__nb_leds; k++){
        this->send_led_trame(leds[k]);
    }
    __enable_irq();
}

void WS2812::set_timings(int t0h, int t0l, int t1h, int t1l){
    this->t0h = t0h;
    this->t0l = t0l;
    this->t1h = t1h;
    this->t1l = t1l;
}


void WS2812::blackout(){
    for(int k = 0; k < this->__nb_leds; k++){
        this->send_led_trame(0);
    }
}