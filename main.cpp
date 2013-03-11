#include "Arduino.h"
#include "bluetooth.hpp"
#include "game.hpp"
#include "canon.hpp"
#include "mot.cpp"

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif

	Serial.begin(9600);
	Serial.println("Initialisation.");

	Bluetooth bt;
	Game game(&bt);
	Canon c;
	Motor motor;
	motor = 0;
	motor.update();
	bool ingame = false;

	Serial.println("Début.");

	for (;;)
	{
end:
		if( !ingame )
		{
			if( !game.waitForDifficulty() )
			{
				Serial.println("Erreur à la réception du niveau de difficulté.");
				ingame = false;
			}
			else
			{
				Serial.println("Début du jeu.");
				game.getDistance();
				ingame = true;
			}
		}
		else
		{
			if( !game.waitComputeOrder() )
			{
				Serial.println("Erreur à la réception de l'ordre de préparation !");
				ingame = false;
				goto end;
			}
			c.load();
			int angle = game.computeAngle();
			Serial.println(angle);
			motor = angle;
			motor.update();
			bt.send("r");

			if( !game.waitFireOrder() )
			{
				Serial.println("Erreur à la réception de l'ordre de tir !");
				ingame = false;
				motor = 0;
				motor.update();
				goto end;
			}
			c.fire();
			bt.send(game.getScore());

			motor = 45;
			motor.update();
		}


		if (serialEventRun) serialEventRun();
	}

	return 0;
}

