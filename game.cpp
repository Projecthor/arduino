#include "game.hpp"
#include "Arduino.h"

const int distPin = 14;

	Game::Game(Bluetooth* connection)
: m_con(connection), m_dif(NONE), m_dist(0), m_score(0)
{
	pinMode(distPin, OUTPUT);
	randomSeed( analogRead(0) ); // Initialisation des valeurs aléatoires
}

bool Game::waitForDifficulty()
{
	unsigned int first = millis();
	char buffer[1];
begin:
	while( m_con->receive(buffer, 1) != 1 )
	{
		// if( millis() - first > m_con->toWait )
		//	return false;
	}

	buffer[0] -= '0';
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
			goto begin;
			break;
	}

	return true;
}

void Game::getDistance()
{
	m_dist = computeDistance();
}

bool Game::waitComputeOrder()
{
	unsigned int first = millis();
	char buffer[2];
beginwait:
	while( m_con->receive(buffer, 2) != 1 )
	{
		// if( millis() - first > m_con->toWait )
		//	return false;
	}

	if( buffer[0] == 'e' )
		return false;
	else if( buffer[0] != 'c' )
		goto beginwait;

	return true;
}
bool Game::waitFireOrder()
{
	unsigned int first = millis();
	char buffer[2];
beginfire:
	while( m_con->receive(buffer, 2) != 1 )
	{
		// if( millis() - first > m_con->toWait )
		//	return false;
	}

	if( buffer[0] == 'e' )
		return false;
	else if( buffer[0] != 'f' )
		goto beginfire;

	return true;
}


int Game::computeAngle()
{
	long prob = random(0, 5);
	bool hasprob = (prob >= 2);
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

	// Le score fait
	if( dist < 25 )
		m_score = 9;
	else if( dist < 50 )
		m_score = 8;
	else if( dist < 75 )
		m_score = 7;
	else if( dist < 100 )
		m_score = 6;
	else if( dist < 133 )
		m_score = 5;
	else if( dist < 166 )
		m_score = 4;
	else if( dist < 200 )
		m_score = 3;
	else if( dist < 250 )
		m_score = 2;
	else
		m_score = 1;

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
	//Lancement de l'ultrason
	pinMode(distPin, OUTPUT);
	digitalWrite(distPin, LOW);
	delayMicroseconds(10);
	digitalWrite(distPin, HIGH);
	delayMicroseconds(15);
	digitalWrite(distPin, LOW);
	delayMicroseconds(20);

	//lecture de l'utrason
	pinMode(distPin, INPUT);
	// return pulseIn(distPin,HIGH) / 29 / 2;
	return 2000;
}

int Game::distFunction(int angle)
{
	float radian = 3.1514 * float(angle) / 180.0;
	float vert = cos(radian); // On calcule le cosinus
	vert *= vert; // On élève au carré
	Serial.println(vert);
	vert *= 2 * origVit * origVit;
	Serial.println(vert);
	Serial.print("dist : ");
	Serial.println(m_dist);
	vert = (gravity * m_dist * m_dist) / vert;
	Serial.println(vert);
	vert *= -1;
	Serial.println(vert);
	vert += m_dist * tan(radian);
	Serial.println(vert);
	vert += decal.x;
	Serial.println(vert);
	return vert;
}

// L'algo procède par dichotomie car la fonction est croissante sur [0;45]
int Game::relToAngle(int dist)
{
	// DEBUG
	Serial.print("Dist : ");
	Serial.println(dist);

	for(int i = 0; i <= 45; ++i)
	{
		Serial.print(i);
		Serial.print("° = ");
		Serial.println(distFunction(i));
	}
	// END DEBUG 

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
			min = angle;
			angle = min + max / 2;
		}
		else
		{
			max = angle;
			angle = min + max / 2;
		}
	}

	return angle;
}

int Game::getScore()
{
	return m_score;
}
