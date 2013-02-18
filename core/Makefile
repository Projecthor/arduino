FLAGS=-Wall -Wextra
APATH=/usr/lib/arduino
CXXFLAGS=$(FLAGS) -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=103 -I $(APATH)/hardware/arduino/cores/arduino/ -I $(APATH)/libraries/SoftwareSerial/ -I $(APATH)/hardware/arduino/variants/standard/ -I $(APATH)/libraries/Servo/
CFLAGS=$(FLAGS) -g -Os -w -fno-exceptions -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=103 -I $(APATH)/hardware/arduino/cores/arduino/ -I $(APATH)/libraries/SoftwareSerial/ -I $(APATH)/hardware/arduino/variants/standard/ -I $(APATH)/libraries/Servo/
FILES=WString.o wiring_digital.o wiring.o wiring_analog.o WInterrupts.o Tone.o Print.o HardwareSerial.o wiring_shift.o wiring_pulse.o Print.o WMath.o SoftwareSerial.o Servo.o


all : $(FILES)
	# avr-ar rcsv core.a *.o

%.o : $(APATH)/hardware/arduino/cores/arduino/%.c
	avr-gcc $(CFLAGS) -c $< -o $@

%.o : $(APATH)/hardware/arduino/cores/arduino/%.cpp
	avr-g++ $(CXXFLAGS) -c $< -o $@

SoftwareSerial.o : $(APATH)/libraries/SoftwareSerial/SoftwareSerial.cpp
	avr-g++ $(CFLAGS) -c $< -o $@

Servo.o : $(APATH)/libraries/Servo/Servo.cpp
	avr-g++ $(CFLAGS) -c $< -o $@

pins_arduino.o : /usr/share/arduino/hardware/arduino/cores/arduino/pins_arduino.c
	avr-g++ $(CFLAGS) -c $< -o $@

clean :
	rm -vf *.o
	rm -vf *.a
