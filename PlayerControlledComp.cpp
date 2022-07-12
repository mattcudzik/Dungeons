#include "PlayerControlledComp.h"

PlayerControlledComp::PlayerControlledComp(float maxSpeed, float acceleration) : m_maxSpeed(maxSpeed), m_acceleration(acceleration) {};

float PlayerControlledComp::GetMaxSpeed() {
	return this->m_maxSpeed;
}

float PlayerControlledComp::GetAcceleration() {
	return this->m_acceleration;
}

void PlayerControlledComp::SetMaxSpeed(float speed) {
	this->m_maxSpeed = speed;
}

void PlayerControlledComp::SetAcceleration(float acceleration) {
	this->m_acceleration = acceleration;
}

Component::ComponentType PlayerControlledComp::GetType() {
	return Component::ComponentType::PlayerControlled;
}