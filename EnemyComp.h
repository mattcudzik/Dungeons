#pragma once
#include "SFML/System.hpp"

#include "Component.h"

class EnemyComp : public Component
{
public:
	enum State
	{
		following,
		shooting
	};
	ComponentType GetType();
	EnemyComp(float maxSpeed, float acceleration);

	float GetMaxSpeed();
	float GetAcceleration();
	void SetMaxSpeed(float speed);
	void SetAcceleration(float acceleration);
	State GetCurrentState();
	void SetCurrentState(State state);
	sf::Clock testClock;

private:
	float m_maxSpeed;
	float m_acceleration;
	State m_currentState;
};

