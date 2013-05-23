all: connect4.hex

connect4.elf: connect4.c
  avr-gcc -mmcu=atmega324p -Os -Wall  -o connect4.elf connect4.c

connect4.hex: connect4.elf
	avr-objcopy  -j .text -j .data -O ihex  connect4.elf connect4.hex
	avr-size connect4.elf

clean:
	rm -rf connect4.elf connect4.hex
