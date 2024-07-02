avr-gcc -mmcu=attiny85 main.c -O1 -o wsad.hex
avrdude -p attiny85 -c usbasp -U flash:w:wsad.hex