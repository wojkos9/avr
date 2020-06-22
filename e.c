#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

ISR (PCINT0_vect)
{
    if (!(PINB & _BV(PINB1))) {
        PORTB &= ~1;
        _delay_ms(25);
        _delay_ms(500);
        _delay_ms(500);
        ADMUX = (ADMUX & 0xf8) | 0;
        PORTD = 0;
        ADCSRA |= _BV(ADSC);

    }
}

ISR(ADC_vect)
{
    uint16_t r = ADC;
    if (r >  512)
        PORTB |= 1;
    else
        PORTB &= ~1;
    PORTD = r >> (10-4);
    ADMUX = (ADMUX & 0xf8) | 0;
    ADCSRA |= _BV(ADSC);
}

void main(void) {
    DDRD = 15;
    DDRB = 1;
    DDRC = 1;
    PORTB = 3;
    PORTD = 15;
    PCMSK0 |= _BV(PCINT1);
    PCICR |= _BV(PCIE0);
    ADMUX |= _BV(REFS0); // | _BV(REFS1) | 
    DIDR0 | _BV(ADC0D);
    ADCSRA |= _BV(ADEN) | _BV(ADIE) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
    
    sei();

    

    
    

    for(;;){
        // while (PINB & 2);
        // _delay_ms(25);
        // if (!(PINB & 2))
        //     PORTB ^= 1;
        // while (!(PINB & 2));
        _delay_ms(2);
        PORTC ^= _BV(PORTC5);
    }
}