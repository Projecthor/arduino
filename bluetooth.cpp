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
	return m_btcard.write(buffer) == size;
}

unsigned int Bluetooth::receive(char* buffer, unsigned int size)
{
	unsigned int i;
	for(i=0; !m_btcard.available() && i < size; ++i)
		buffer[i] = m_btcard.read();
	return i;
}

bool Bluetooth::connected()
{
	return m_btcard.isListening();
}


