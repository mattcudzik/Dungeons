#pragma once
#include "Component.h"
#include "SFML/System.hpp"


class PlayerControlledComp : public Component
{
public:
	float GetMaxSpeed();
	float GetAcceleration();
	void SetMaxSpeed(float speed);
	void SetAcceleration(float acceleration);
	ComponentType GetType();
	PlayerControlledComp(float maxSpeed, float acceleration);
private:
	float m_maxSpeed;
	float m_acceleration;
};

