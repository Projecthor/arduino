NAME=projector
OBJ=main.o
OBJS=mot.o bluetooth.o canon.o game.o
AVRP=/usr/lib/arduino/hardware/tools/avr/bin/
FLAGS=-g -Os -w -fno-exceptions -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=103 -I /usr/lib/arduino/hardware/arduino/cores/arduino/ -I /usr/lib/arduino/libraries/SoftwareSerial/ -I /usr/lib/arduino/libraries/Servo/ -I /usr/lib/arduino/hardware/arduino/variants/standard/
PORT=/dev/ttyUSB0
BAUDRATE=57600

$(NAME).hex : $(OBJS) $(OBJ)
	cd core && make
	avr-ar rcsv core.a core/*.o $(OBJS)
	avr-gcc -Os -Wl,--gc-sections -mmcu=atmega328p -o $(NAME).elf $(OBJ) core.a -L core -lm
	avr-objcopy -O ihex -R .eeprom $(NAME).elf $(NAME).hex

%.o : %.cpp
	avr-g++ $(FLAGS) -c $< -o $@

transmit : $(NAME).hex
	$(AVRP)/../../avrdude -C /usr/lib/arduino/hardware/tools/avrdude.conf -v -p m328p -P $(PORT) -b$(BAUDRATE) -c arduino -U flash:w:$(NAME).hex

connect : transmit
	screen $(PORT) 9600

clean :
	rm -vf $(OBJS)
	rm -vf $(NAME).{elf,hex}

mr-proper : clean
	rm -vf core.a
	cd core && touch tmp.o tmp.a
	cd core && make clean

rec : clean $(NAME).hex

.PHONY:clean connect transmit rec mr-proper


