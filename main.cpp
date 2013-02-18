#include "Arduino.h"
#include "bluetooth.hpp"
#include "game.hpp"
#include "canon.hpp"

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
				// game.getDistance();
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
			bt.send("r");

			if( !game.waitFireOrder() )
			{
				Serial.println("Erreur à la réception de l'ordre de tir !");
				ingame = false;
				goto end;
			}
			c.fire();
			bt.send(game.getScore());
		}


		if (serialEventRun) serialEventRun();
	}

	return 0;
}

