#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

void freq(int us, int nc) {
	
	while (nc--) {
		int a = us;
		PORTB |= (1<<PORTB0);
		//_delay_us(1136);
		while(a--) _delay_us(1);
		//while(us--) _delay_us(10);
		PORTB &= ~ (1<<PORTB0);
		a = us;
		while(a--) _delay_us(1);
		//while(us1--) _delay_us(10);
	}
	
}
#define TEMPO 120
#define N16 (60.f/TEMPO/4)
void note(int i, int l) {
	float f = 440.f*powf(2, (float)i/12);
	float ms = 500/f;
	int nc = N16*l*f*0.8f;
	freq(ms*1000, nc);
}

int main(void)
{
	char notes[] = {12, 7, 6, 5, 3, 0, 3, 5};
	char lens[] =  {2, 3, 2, 2, 2, 1, 1, 1};
	char begs[] = {0, -2, -3, -4};
	DDRB |= (1<<DDB1);
    int i = 0;
	PORTB |= 2;
    while (1) 
    {	
		for (int j = 0; j < 4; j++) {
			note(begs[j], 1);
			note(begs[j], 1);
			for (i=0; i < sizeof(notes)/sizeof(notes[0]); i++) {
				note(notes[i],lens[i]);
			}
			PORTB ^= 2;
		}
		break;
    }
	_delay_ms(500);
	PORTB &= ~2;
}
