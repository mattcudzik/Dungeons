#include "AccelerationComp.h"
Component::ComponentType AccelerationComp::GetType()
{
	return Component::ComponentType::Acceleration;
}
sf::Vector2f AccelerationComp::GetAcceleration()
{
	return this->acceleration;
}
void AccelerationComp::SetAcceleration(sf::Vector2f acceleration)
{
	this->acceleration = acceleration;
}
AccelerationComp::AccelerationComp() : acceleration(sf::Vector2f(0.0f,0.0f)) {}