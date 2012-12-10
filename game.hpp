
#ifndef DEF_GAME
#define DEF_GAME

#include "bluetooth.hpp"

class Game
{
	public:
		enum Difficulty{EASY,NORMAL,DIFFICULT,DIVINITY,NONE};

		Game(Bluetooth* connection);
		~Game();

		bool waitForDifficulty(); // Si false fin du jeu
		void getDistance();

		bool waitOrder(); // Attend l'ordre de tirer -> si false fin du jeu
		int computeAngle(); // détermine l'angle de tir
		bool checkSecurity(); // Teste si quelqu'un passe devant, renvoie vrai si qqun

	private:
		Bluetooth* m_con; // connection
		Difficulty m_dif;
		unsigned int m_dist; // Distance de la cible en mm

		unsigned int computeDistance();

		const int maxMov = 2000; // différence maxi lors de la détection d'obstacle en mm
};

#endif//DEF_GAME

