#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char cmd[4];
uint8_t ix = 0;

ISR(PCINT1_vect) {
    if (!(PINC & _BV(PINC5))) {
        _delay_ms(25);
        if (!(PINC & _BV(PINC5))) {
            PORTB ^= _BV(PORTB0);
        }
        
    }
}

ISR(PCINT0_vect) {
    if (PINB & _BV(PINB2))
        PORTB |= _BV(PORTB0);
    else
        PORTB &= ~(_BV(PORTB0));
}

void main(void) {
    DDRB = _BV(DDB0) | _BV(DDB4);
    PORTC = _BV(PCINT13);

    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PCINT13);
    //DDR_SPI = (1<<DD_MISO);

    PCICR |= _BV(PCIE0);
    PCMSK1 |= _BV(PCINT2);
    
    SPCR =  _BV(SPE) | _BV(SPIE);

    sei();
    
    for(;;) {
        while(!(SPSR & (1<<SPIF)));
        cmd[ix] = SPDR;
        SPDR = cmd[ix];
        ix = (ix+1)%4;

        if (PINB & _BV(PINB2))
            PORTB |= _BV(PORTB0);
        else
            PORTB &= ~(_BV(PORTB0));
    }
    
}