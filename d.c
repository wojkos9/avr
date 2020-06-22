#include <avr/io.h>
#include <util/delay.h> 
#include "wave.h"

void main() {
    DDRD |= 31;
    //uint8_t u = 0;
    uint8_t l = sizeof(wave);
    uint8_t i = 0;
    for(;;) {
        _delay_us(1000000/8000);
        i = ++i % l;
        //u = wave[i];
        //u = (u+1)&7;//wave[i] & 7;
        PORTD = wave[i];
    }
}