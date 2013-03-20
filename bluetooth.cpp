#include "bluetooth.hpp"

Bluetooth::Bluetooth()
	: m_btcard(6,7)
{
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);

	pinMode(6, INPUT);
	pinMode(7, OUTPUT);

	m_btcard.begin(38400);
	m_btcard.print("\r\n+STWMOD=0\r\n");
	m_btcard.print("\r\n+STNA=Projecthor01\r\n");
	m_btcard.print("\r\n+STOAUT=1\r\n");
	m_btcard.print("\r\n+STAUTO=0\r\n");
	digitalWrite(13, LOW);
	delay(2000);

	m_btcard.print("\r\n+INQ=1\r\n");
	// Serial.println("The slave bluetooth is inquirable!");
	delay(2000);
	m_btcard.flush();
}

bool Bluetooth::waitForConnection(callback cb, void* data)
{
	unsigned int last = millis();
	while( !connected() )
	{
		if( cb != NULL )
			cb(data);

		if( millis() - last > toWait )
			return false;
	}
	
	return true;
}

unsigned int Bluetooth::receive(char* buffer, unsigned int size)
{
	unsigned int i;
	for(i=0; m_btcard.available() && i < size; ++i)
		buffer[i] = m_btcard.read(); // + 128;
	return i;
}

bool Bluetooth::connected()
{
	// TODO à tester
	return m_btcard.isListening();
}


