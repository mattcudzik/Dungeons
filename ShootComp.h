#pragma once
#include "Component.h"
#include "SFML/System.hpp"
#include "ProjectileComp.h"

#include <random>

class ShootComp : public Component
{

public:
	ComponentType GetType();
	float GetCooldownTime();
	float GetElapsedTime();
	float GetProjectileSpeed();
	void SetProjectileSpeed(float speed);
	void ResetClock();
	ProjectileComp::Target GetTarget();
	ProjectileComp::Type GetProjectileType();
	ShootComp(float cooldownTime, ProjectileComp::Target projectileTarget, ProjectileComp::Type type, float projectileSpeed = 60.f);

	sf::Vector2f GetShootDirection();
	void SetShootDirection(sf::Vector2f direction);

private:
	float m_projectileSpeed;
	sf::Clock m_shootCooldownClock;
	float m_cooldownTime;
	sf::Vector2f m_shootDirection;
	ProjectileComp::Target m_projectileTarget;
	ProjectileComp::Type m_projectileType;
};


