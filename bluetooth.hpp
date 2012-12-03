
#ifndef DEF_BLUETOOTH
#define DEF_BLUETOOTH

class Bluetooth
{
	public:
		const int toWait = 15000; // Temps à attendre en millisecondes

		Bluetooth();
		Bluetooth();

		bool waitForConnection(); // Attend une connection, retourne false si temps dépassé
		bool send(char* buffer, unsigned int size);
		unsigned int receive(char* buffer, unsigned int size); // Retourne le nombre d'octets lus
		bool connected(); // Teste si la connection est valide

	private:
};

#endif//DEF_BLUETOOTH

