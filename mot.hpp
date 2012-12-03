
#ifndef DEF_MOTOR
#define DEF_MOTOR

class Motor
{
	public:
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
};

#endif//DEF_MOTOR

