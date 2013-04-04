
#ifndef DEF_GAME
#define DEF_GAME

#include "bluetooth.hpp"

class Game
{
	public:
		enum Difficulty{EASY,NORMAL,DIFFICULT,DIVINITY,NONE};

		Game(Bluetooth* connection);

		bool waitForDifficulty(); // Si false fin du jeu
		void getDistance();

		bool waitComputeOrder(); // Attend l'ordre de charger -> si false fin du jeu
		bool waitFireOrder(); // Attend l'ordre de tirer -> si false fin du jeu
		int computeAngle(); // détermine l'angle de tir
		int getScore();
		bool checkSecurity(); // Teste si quelqu'un passe devant, renvoie vrai si qqun

	private:
		Bluetooth* m_con; // connection
		Difficulty m_dif;
		unsigned int m_dist; // Distance de la cible en mm
		int m_score;

		unsigned int computeDistance();
		int relToAngle(int dist); // convertit une distance verticale par rapport au centre de la cible en angle nécessaire
		int distFunction(int angle); // lie l'angle à la distance verticale sur la cible

		const unsigned int maxMov = 30; // différence maxi lors de la détection d'obstacle en mm
		const unsigned int sizeCible = 600; // Hauteur de la cible en mm
		const unsigned int midCible = sizeCible / 2; // Milieu de la cible
		const unsigned int thirdCible = midCible / 3;
		// const unsigned int origVit = 6260; // vitesse à la sortie du canon en mm/s
		const unsigned int origVit = 8000; // vitesse à la sortie du canon en mm/s
		const unsigned int gravity = 10000; // La force gravitationelle en mm/s²
		struct Pos
		{
			unsigned int x;
			unsigned int y;
		};
		const Pos decal = {x : 160, y : 240}; // Décalage du centre de rotation du canon par rapport au capteur de distance.
};

#endif//DEF_GAME

