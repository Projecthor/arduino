#include "game.hpp"
#include "Arduino.h"

	Game::Game(Bluetooth* connection)
: m_con(connection), m_dif(NONE), m_dist(0)
{
	// TODO initialisation capteur de distance

	randomSeed( analogRead(0) ); // Initialisation des valeurs aléatoires
}

Game::~Game()
{
	// TODO libération capteur de distance
}

bool Game::waitForDifficulty()
{
	// TODO éviter boucle infinie
	char buffer[1];
	while( m_con->receive(buffer, 1) != 1 )
	{
		switch( buffer[0] )
		{
			case 0:
				m_dif = EASY;
				break;
			case 1:
				m_dif = NORMAL;
				break;
			case 2:
				m_dif = DIFFICULT;
				break;
			case 3:
				m_dif = DIVINITY;
				break;
			default:
				buffer[0] = 0xff;
				return false;
				break;
		}

		m_con->send(buffer, 1);
	}
	return true;
}

void Game::getDistance()
{
	m_dist = computeDistance();
}

bool Game::waitOrder()
{
	// TODO éviter boucle infinie
	char buffer[2];
	while( m_con->receive(buffer, 2) != 2 )
	{
		if( buffer[0] != 0x0f )
			return false;
		buffer[0] = 0xf0;
		m_con->send(buffer, 2);
	}
	return true;
}

int Game::computeAngle()
{
	// TODO calculer l'angle en fonction du niveau de difficulté
	long prob = random(0, 5);
	bool hasprob = prob >= 2;
	int dist;

	switch(m_dif)
	{
		case EASY:
			if( hasprob )
				dist = random(2 * thirdCible, midCible);
			else
				dist = random(0, 2 * thirdCible);
			break;
		case NORMAL:
			dist = random(0, midCible);
			if( hasprob )
			{
				dist /= 3;
				dist += thirdCible;
			}
			else if( dist >= thirdCible )
				dist += thirdCible;
			break;
		case DIFFICULT:
			dist = random(0, midCible);
			if( hasprob )
				dist /= 3;
			break;
		case DIVINITY:
			dist = 0;
			break;
	}
	if( random(0,2) == 0 )
		dist *= -1;

	return relToAngle(dist);
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

