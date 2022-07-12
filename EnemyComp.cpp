#include "EnemyComp.h"
Component::ComponentType EnemyComp::GetType()
{
	return Component::ComponentType::Enemy;
}

EnemyComp::EnemyComp(float maxSpeed, float acceleration) : m_maxSpeed(maxSpeed), m_acceleration(acceleration), m_currentState(State::following) {};


float EnemyComp::GetMaxSpeed()
{
	return this->m_maxSpeed;
}

float EnemyComp::GetAcceleration()
{
	return this->m_acceleration;
}

void EnemyComp::SetMaxSpeed(float speed)
{
	this->m_maxSpeed = speed;
}

void EnemyComp::SetAcceleration(float acceleration)
{
	this->m_acceleration = acceleration;
}

EnemyComp::State EnemyComp::GetCurrentState()
{
	return this->m_currentState;
}

void EnemyComp::SetCurrentState(State state)
{
	this->m_currentState = state;
}