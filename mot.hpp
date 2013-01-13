
#ifndef DEF_MOTOR
#define DEF_MOTOR

#include <Servo.h>

class Motor
{
	public:
		const int mot_pin = 9;

		Motor();
		~Motor();

		int currentAngle() const;
		int destAngle() const;
		Motor& operator=(int angle);
		Motor& operator+=(int angle);
		Motor& operator-=(int angle);
		void update();

	private: 
		int m_angle; // Angle actuel en degrés
		int m_dest; // Angle à obtenir en gegrés
		Servo m_mot;
};

#endif//DEF_MOTOR

