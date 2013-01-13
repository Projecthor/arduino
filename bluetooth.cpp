#include "bluetooth.hpp"

Bluetooth::Bluetooth()
	: m_btcard(6,7)
{
	pinMode(6, INPUT);
	pinMode(7, OUTPUT);

	m_btcard.begin(38400);
	m_btcard.print("\r\n+STWMOD=0\r\n");
	m_btcard.print("\r\n+STNA=SeeedBTSlave\r\n");
	m_btcard.print("\r\n+STOAUT=1\r\n");
	m_btcard.print("\r\n+STAUTO=0\r\n");
	delay(2000);

	m_btcard.print("\r\n+INQ=1\r\n");
	Serial.println("The slave bluetooth is inquirable!");
	delay(2000);
	m_btcard.flush();
}

Bluetooth::~Bluetooth()
{}

bool Bluetooth::waitForConnection(callback cb, void* data)
{
	unsigned int last = millis();
	while( !m_btcard.isListening() )
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
	return m_btcard.print(buffer) == size;
}

unsigned int Bluetooth::receive(char* buffer, unsigned int size)
{
	unsigned int i;
	for(i=0; m_btcard.available() && i < size; ++i)
		buffer[i] = m_btcard.read();
	return i;
}

bool Bluetooth::connected()
{
	// TODO à tester
	return m_btcard.isListening();
}


