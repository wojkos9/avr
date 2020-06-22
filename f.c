#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "cbuf.h"

#define even_after(ms, cond) (cond) && (_delay_ms((ms)), (cond))

//#define F_CPU 16000000L
#define BAUD 9600
#define BRC (F_CPU/16/BAUD-1)

ISR(USART_TX_vect) {
    // UDR0 =!(i%27)?'\r':(i<27?96+i:64+(i-27));
    // i = (i+1)%54;
    //_delay_ms(1);
    char c;
    if (c = creadc(csout)) {
        UDR0 = c;
        //_delay_ms(10);
    }
}

void usart_write(char *buf, int n) {
    char *end = buf+n;
    for (; buf != end; buf++){
        cputc(csout, *buf);
    }
    UDR0 = creadc(csout);
}
int usart_read(char *buf, int n) {
    char *end = buf+n;
    int r = 0;
    usart_write("read\r\n", 6);
    char c;
    while (buf != end) {
        while(!(c = creadc(ccsin)));
        *buf = c;
        usart_write("x", 1);
        r++;
        if (c == '\n')
            break;
        //r++;
        buf++;
        
    }
    return r;
}

ISR(PCINT1_vect) {
    //if (even_after(25, !(PINC & _BV(PCINT13)))) {
    if (!(PINC & _BV(PCINT13))) {
        usart_write("czesc\n\r", 7);
    }
}
ISR(USART_RX_vect) {
    char c = UDR0;
    usart_write("|", 1);
    cputc(ccsin, c);
    //char bb[4] = {'R', c, '\r', '\n'};
    usart_write(ccsin->buf, ccsin->nchar);
    usart_write(" ", 1);
    char q = (ccsin->h-ccsin->buf)+'1';
    usart_write(&q, 1);
    q = (ccsin->t-ccsin->buf)+'1';
    usart_write(&q, 1);
    usart_write("\r\n", 2);
}

void main(void) {
    cinit();
    DDRB = 1;
    //PORTB = 1;
    PORTC = _BV(PCINT13);
    PCMSK1 |= _BV(PCINT13);
    PCICR |= _BV(PCIE1);
    UBRR0H = BRC >> 8;
    UBRR0L = BRC;
    UCSR0B = _BV(TXEN0) | _BV(RXEN0) | _BV(TXCIE0) | _BV(RXCIE0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    sei();
    char bb[BUFSZ];
    int l;
    for(;;) {
        while (!(l = usart_read(bb, BUFSZ)));
        usart_write(bb, l);
    }
}