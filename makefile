a: a.c
	avr-gcc -mmcu=atmega328p -std=gnu99 a.c -oa -O3
b: b.c
	avr-gcc -mmcu=atmega328p -std=gnu99 b.c -ob -O3
install:
	sudo avrdude -p atmega328p -c usbasp -U flash:w:a
ib:
	sudo avrdude -p atmega328p -c usbasp -U flash:w:b
