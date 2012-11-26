FILES=projecthor.cpp
OBJ=obj
FLAGS=-g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=22 -I /usr/share/arduino/hardware/arduino/cores/arduino/
PORT=/dev/ttyUSB0
BAUDRATE=57600

$(OBJ).hex : $(OBJ).o
	cd core && touch tmp.o tmp.a
	cd core && make clean
	cd core && make
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega328p -o $(OBJ).elf $^ ./core/core.a -L core -lm
	avr-objcopy -O ihex -R .eeprom $(OBJ).elf $(OBJ).hex

$(OBJ).o : $(FILES)
	avr-g++ $(FLAGS) -c $^ -o $@

transmit : $(OBJ).hex
	avrdude -v -p m328p -P $(PORT) -b$(BAUDRATE) -c arduino -U flash:w:$(OBJ).hex

connect : transmit
	screen $(PORT) $(BAUDRATE)

clean :
	cd core && touch tmp.o tmp.a
	cd core && make clean
	rm -vf $(OBJ).o
	rm -vf $(OBJ).elf
	rm -vf $(OBJ).hex

.PHONY:clean connect transmit


