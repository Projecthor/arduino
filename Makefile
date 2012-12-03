NAME=projector
OBJS=projecthor.o mot.o bluetooth.o
FLAGS=-g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=22 -I /usr/share/arduino/hardware/arduino/cores/arduino/
PORT=/dev/ttyUSB0
BAUDRATE=57600

$(NAME).hex : $(OBJS)
	cd core && make
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega328p -o $(NAME).elf $^ ./core/core.a -L core -lm
	avr-objcopy -O ihex -R .eeprom $(NAME).elf $(NAME).hex

%.o : %.cpp
	avr-g++ $(FLAGS) -c $< -o $@

transmit : $(NAME).hex
	avrdude -v -p m328p -P $(PORT) -b$(BAUDRATE) -c arduino -U flash:w:$(NAME).hex

connect : transmit
	screen $(PORT) $(BAUDRATE)

clean :
	rm -vf $(OBJS)
	rm -vf $(NAME).{elf,hex}

mr-proper : clean
	cd core && touch tmp.o tmp.a
	cd core && make clean

rec : clean $(NAME).hex

.PHONY:clean connect transmit rec mr-proper


