FLAGS=-Wall -Wextra
CXXFLAGS=$(FLAGS) -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=22 -I /usr/lib/arduino/hardware/arduino/cores/arduino/ -I /usr/lib/arduino/hardware/arduino/variants/standard/
CFLAGS=$(FLAGS) -g -Os -w -fno-exceptions -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=22 -I /usr/lib/arduino/hardware/arduino/cores/arduino/ -I /usr/lib/arduino/hardware/arduino/variants/standard/
FILES=WString.o wiring_digital.o wiring.o wiring_analog.o WInterrupts.o Tone.o Print.o pins_arduino.o main.o HardwareSerial.o wiring_shift.o wiring_pulse.o Print.o WMath.o


all : $(FILES)
	avr-ar rcsv core.a *.o

%.o : /usr/lib/arduino/hardware/arduino/cores/arduino/%.c
	avr-gcc $(CFLAGS) -c $< -o $@

%.o : /usr/lib/arduino/hardware/arduino/cores/arduino/%.cpp
	avr-g++ $(CXXFLAGS) -c $< -o $@

clean :
	rm -vf *.o
	rm -vf *.a
