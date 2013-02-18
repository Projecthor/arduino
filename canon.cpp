#include "canon.hpp"
#include "Arduino.h"

Canon::Canon()
{
	Serial.begin(9600);
	Serial.println("Canon !");
	// TODO initialiser canon
}

void Canon::load()
{
	// TODO faire charger le canon
	Serial.println("Chargement du canon.");
}

void Canon::fire()
{
	// TODO déclencher le tir
	Serial.println("FIRE !!!");
}



