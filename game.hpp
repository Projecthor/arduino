
#ifndef DEF_GAME
#define DEF_GAME

#include "bluetooth.hpp"

class Game
{
	public:
		enum Difficulty{VEASY,EASY,NORMAL,MEDIUM,DIFFICULT,DIVINITY};

		Game(Bluetooth connection);
		~Game();

		bool waitForDifficulty(); // Si false fin du jeu
		void getDistance();

		bool waitOrder(); // Attend l'ordre de tirer -> si false fin du jeu
		int computeAngle(); // détermine l'angle de tir
		bool checkSecurity(); // Teste si quelqu'un passe devant

	private:
		Bluetooth* m_con; // connection
		Difficulty m_dif;
		unsigned int m_dist; // Distance de la cible en cm

		unsigned int computeDistance();
};

#endif//DEF_GAME

