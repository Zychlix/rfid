avr-gcc -mmcu=atmega328 arduin.c -O1 -o wsad.hex
avrdude -p m328p -c arduino -U flash:w:wsad.hex -P/dev/ttyUSB0
