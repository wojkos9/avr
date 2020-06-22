#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void) {
    //DDRB |= (1 << DDB0);
    uint8_t u = 0;
    for (;;) {
        _delay_us(1000000/440);
        PORTB ^= (1);
        // u = (u + 1) & 7;
        // PORTB = u;
        // PORTD ^= (1 << 7);
    }

}