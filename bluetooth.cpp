#include "bluetooth.hpp"

Bluetooth::Bluetooth()
{
	// TODO initialiser module bluetooth
}

Bluetooth::~Bluetooth()
{
	// TODO libérer module bluetooth
}

bool Bluetooth::waitForConnection(callback cb)
{
	// TODO attendre connection entrante
}

bool Bluetooth::send(char* buffer, unsigned int size)
{
	// TODO envoyer un message
}

unsigned int Bluetooth::receive(char* buffer, unsigned int size)
{
	// TODO recevoir un message
}

bool Bluetooth::connected()
{
	// TODO tester la connection
}


