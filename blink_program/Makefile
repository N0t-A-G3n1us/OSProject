# MAKEFILE instructables

# fatto da chunks chiamati "recipe", hanno formato standard:
#		|target: dependecies
#		|	action


# nome file da compilare (senza estensione)

PROG_NAME=blink

# porta da modificare in base a quale è connesso arduino (possibile vederlo da ide)

PORT=/dev/ttyACM0


all: build 

build: 
	@echo '\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\'
	@echo " usage:" 
	@echo '  $$$  make     to compile'
	@echo '  $$$  make program     to exec' 
	@echo '/////////////////////////////////'
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $(PROG_NAME).o $(PROG_NAME).c
	avr-gcc -mmcu=atmega328p $(PROG_NAME).o -o $(PROG_NAME)
	avr-objcopy -O ihex -R .eeprom $(PROG_NAME) $(PROG_NAME).hex
	
program:
	avrdude -v -v -v -v -p atmega328p -c arduino -P $(PORT) -b 115200 -D -U flash:w:$(PROG_NAME).hex
	
clean:
	rm -rf $(PROG_NAME) *.o *.hex $(PROG_NAME).elf

