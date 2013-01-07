#include "mot.hpp"

Motor::Motor()
	: m_angle(0), m_dest(0)
{
	// TODO initialisation du moteur
}

Motor::~Motor()
{
	// TODO libération du moteur
}

int Motor::currentAngle() const
{
	return m_angle;
}

int Motor::destAngle() const
{
	return m_dest;
}

Motor& Motor::operator=(int angle)
{
	if(angle >= 45)
		m_dest = 45;
	else if(angle <= 0)
		m_dest = 0;
	else
		m_dest = angle;
	return *this;
}

Motor& Motor::operator+=(int angle)
{
	angle = m_dest + angle;
	return (*this = angle);
}

Motor& Motor::operator-=(int angle)
{
	angle = m_dest - angle;
	return (*this = angle);
}

void Motor::update()
{
	// TODO Rotation du moteur
}

