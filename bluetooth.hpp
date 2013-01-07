
#ifndef DEF_BLUETOOTH
#define DEF_BLUETOOTH

#include "Arduino.h"

class Bluetooth
{
	public:
		const int toWait = 15000; // Temps à attendre en millisecondes
		typedef void(*callback)(void*);

		Bluetooth();
		~Bluetooth();

		bool waitForConnection(callback cb, void* data); // Attend une connection, retourne false si temps dépassé. La fonction cb sera appelé régulièrement si cb est différent de NULL.
		bool send(char* buffer, unsigned int size);
		unsigned int receive(char* buffer, unsigned int size); // Retourne le nombre d'octets lus
		bool connected(); // Teste si la connection est valide

	private:
		SoftwareSerial m_btcard;
};

#endif//DEF_BLUETOOTH

