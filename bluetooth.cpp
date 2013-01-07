#include "bluetooth.hpp"

Bluetooth::Bluetooth()
	: m_btcard(0,1)
{
	m_btcard.begin(9600);
}

Bluetooth::~Bluetooth()
{}

bool Bluetooth::waitForConnection(callback cb, void* data)
{
	unsigned int last = millis();
	while( !m_btcard )
	{
		if( cb != NULL )
			cb(data);

		if( millis() - last > toWait )
			return false;
	}
	
	return true;
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


