
#ifndef DEF_CANON
#define DEF_CANON

const int loadPin = 2;
const int firePin = 3;
const unsigned long loadTime = 2000;

class Canon
{
	public:
		Canon();

		void load(); // Fonction bloquuante, charge le canon
		void fire();

	private:
};

#endif//DEF_CANON

