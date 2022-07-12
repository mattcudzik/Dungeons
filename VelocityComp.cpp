#include "VelocityComp.h"
Component::ComponentType VelocityComp::GetType()
{
	return Component::ComponentType::Velocity;
}
sf::Vector2f VelocityComp::GetDirection() 
{
	return this->direction;
}
sf::Vector2f VelocityComp::GetVelocity()
{
	return this->velocity;
}
void VelocityComp::SetDirection(sf::Vector2f direction)
{
	this->direction = direction;
}
void VelocityComp::SetVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

VelocityComp::VelocityComp() : velocity(sf::Vector2f(0.0f,0.0f)), direction(sf::Vector2f(0.0f,0.0f)) {}
VelocityComp::VelocityComp(sf::Vector2f iniVelocity, sf::Vector2f iniDir) : velocity(iniVelocity), direction(iniDir) {}