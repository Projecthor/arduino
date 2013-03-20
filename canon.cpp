#include "canon.hpp"
#include "Arduino.h"

Canon::Canon()
{
	Serial.begin(9600);
	Serial.println("Canon !");

	pinMode(firePin, OUTPUT);
	digitalWrite(firePin, LOW);
	pinMode(loadPin, OUTPUT);
	digitalWrite(loadPin, LOW);
}

void Canon::load()
{
	Serial.println("Chargement du canon.");

	unsigned long ltime = millis();
	while(millis() - ltime < loadTime)
	{
		digitalWrite(loadPin, LOW);
		delay(50);
		digitalWrite(loadPin, HIGH);
		delay(50);
	}
	digitalWrite(loadPin, LOW);
}

void Canon::fire()
{
	Serial.println("FIRE !!!");

	digitalWrite(firePin, HIGH);
	delay(2000);
	digitalWrite(firePin, LOW);
}



