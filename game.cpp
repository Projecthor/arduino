#include "game.hpp"

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

