#pragma once
#include "Component.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class ProjectileComp : public Component
{
public:
	enum Target
	{
		Player,
		Enemy
	};
	enum Type
	{
		Projectile = 0,
		Arrow
	};
	ComponentType GetType();
	ProjectileComp(Target source, Type type);
	Target GetProjectileTarget();
	Type GetProjectileType();
private:
	Target m_target;
	Type m_type;
};

