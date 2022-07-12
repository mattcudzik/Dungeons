#include "ShootComp.h"

ShootComp::ShootComp(float cooldownTime, ProjectileComp::Target projectileTarget, ProjectileComp::Type type, float projectileSpeed)
	: m_cooldownTime(cooldownTime), m_shootDirection(sf::Vector2f(0.f, 0.f)),
	m_projectileTarget(projectileTarget), m_projectileSpeed(projectileSpeed), m_projectileType(type) {};

Component::ComponentType ShootComp::GetType()
{
	return Component::ComponentType::Shoot;
}

float ShootComp::GetCooldownTime()
{
	return this->m_cooldownTime;
}

float ShootComp::GetElapsedTime()
{
	return this->m_shootCooldownClock.getElapsedTime().asSeconds();
}

void ShootComp::ResetClock()
{
	this->m_shootCooldownClock.restart();
}
sf::Vector2f ShootComp::GetShootDirection()
{
	return this->m_shootDirection;
}
void ShootComp::SetShootDirection(sf::Vector2f direction)
{
	this->m_shootDirection = direction;
}
ProjectileComp::Target ShootComp::GetTarget()
{
	return this->m_projectileTarget;
}
float ShootComp::GetProjectileSpeed()
{
	return this->m_projectileSpeed;
}
void ShootComp::SetProjectileSpeed(float speed)
{
	this->m_projectileSpeed = speed;
}
ProjectileComp::Type ShootComp::GetProjectileType()
{
	return this->m_projectileType;
}