#include "game.hpp"
#include "Arduino.h"

	Game::Game(Bluetooth* connection)
: m_con(connection), m_dif(NONE), m_dist(0)
{
	// TODO initialisation capteur de distance
}

Game::~Game()
{
	// TODO libération capteur de distance
}

bool Game::waitForDifficulty()
{
	// TODO protocole bluetooth
}

void Game::getDistance()
{
	m_dist = computeDistance();
}

bool Game::waitOrder()
{
	// TODO protocole bluetooth
}

int Game::computeAngle()
{
	// TODO calculer l'angle en fonction du niveau de difficulté
}

bool Game::checkSecurity()
{
	int diff = computeDistance() - m_dist;
	diff *= (diff < 0 ? -1 : 1);

	if( diff >= maxMov )
		return true;
	else
		return false;
}

unsigned int Game::computeDistance()
{
	// TODO récupère la distance
}

int Game::distFunction(int angle)
{
	int radian = 3.1514 * float(angle) / 180.0;
	long vert = cos(radian); // On calcule le cosinus
	vert *= vert; // On élève au carré
	vert *= 2 * origVit * origVit;
	vert = gravity * m_dist * m_dist / vert;
	vert *= -1;
	vert += m_dist * tan(radian);
	vert += decal.x;
	return vert;
}

// L'algo procède par dichotomie car la fonction est croissante sur [0;45]
int Game::relToAngle(int dist)
{
	int angle = 22;
	int min = 0, max = 45;
	int ldist;
	bool continuer = true;

	while( continuer )
	{
		ldist = distFunction(angle);
		if( max - min <= 1 
				|| ldist == dist )
			continuer = false;
		else if( ldist < dist )
		{
			max = angle;
			angle = min + max / 2;
		}
		else if( ldist > dist )
		{
			min = angle;
			angle = min + max / 2;
		}
	}

	return angle;
}

